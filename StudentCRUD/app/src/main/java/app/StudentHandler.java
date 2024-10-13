package app;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.charset.StandardCharsets;
import java.sql.Date;
import java.util.List;

import org.json.JSONArray;
import org.json.JSONObject;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;

public class StudentHandler implements HttpHandler {

    @Override
    public void handle(HttpExchange exchange) throws IOException {

        String method = exchange.getRequestMethod();
        String path = exchange.getRequestURI().getPath();
        String params = path.substring("/api/students".length()).replaceAll("^/|/$", "");


        try {
            if ("OPTIONS".equalsIgnoreCase(method)) {
                handleOptionsRequest(exchange);
                return;
            }

            if ("GET".equalsIgnoreCase(method) && params.isBlank()) {
                getAllStudents(exchange);
            } else if ("POST".equalsIgnoreCase(method) && params.isBlank()) {
                createStudent(exchange);
            } else if ("DELETE".equalsIgnoreCase(method) && !params.isBlank()) {
                deleteStudent(exchange, params);
            } else {
                sendResponse(exchange, 405, "Method Not Allowed");
            }
        } catch (IOException e) {
            e.printStackTrace();
            sendResponse(exchange, 500, "Some Server Error");
        }

    }

    private void createStudent(HttpExchange exchange) throws IOException {
        StudentDAO operations = new StudentDAO();

        InputStream is = exchange.getRequestBody();
        String requestBody = new String(is.readAllBytes(), StandardCharsets.UTF_8);

        JSONObject json = new JSONObject(requestBody);
        String firstName = json.getString("firstName");
        String lastName = json.getString("lastName");
        String middleName = json.optString("middleName", "");
        Date birthDate = Date.valueOf(json.getString("birthDate"));
        String group = json.getString("studentGroup");

        Student newStudent = new Student(firstName, lastName, middleName, birthDate, group);
        boolean isCreated = operations.createStudent(newStudent);

        String response = isCreated ? "Created successfully!" : "Oops!";
        int code = isCreated ? 201 : 500;
        sendResponse(exchange, code, response);
    }

    private void deleteStudent(HttpExchange exchange, String id) throws IOException {
        StudentDAO operations = new StudentDAO();
        try {
            boolean isDeleted = operations.deleteStudent(Integer.parseInt(id));

            String response = isDeleted ? "Deleted successfully!" : "Not found!";
            int code = isDeleted ? 200 : 400;
            sendResponse(exchange, code, response);
        } catch (NumberFormatException e) {
            sendResponse(exchange, 400, "Incorrect ID!");
        }
    }

    // TODO fix id always equals 0
    private void getAllStudents(HttpExchange exchange) throws IOException {
        StudentDAO operations = new StudentDAO();
        JSONArray jsonArray = new JSONArray();
        List<Student> students = operations.getAllStudents();

        for (Student student : students) {
            JSONObject jsonObject = new JSONObject();
            jsonObject.put("id", student.getId());
            jsonObject.put("firstName", student.getFirstName());
            jsonObject.put("lastName", student.getLastName());
            jsonObject.put("middleName", student.getMiddleName());
            jsonObject.put("birthDate", student.getBirthDate().toString());
            jsonObject.put("studentGroup", student.getStudentGroup());
            jsonArray.put(jsonObject);
        }

        String response = jsonArray.toString();
        exchange.getResponseHeaders().set("Content-Type", "application/json; charset=UTF-8");
        sendResponse(exchange, 200, response);
    }

    private void handleOptionsRequest(HttpExchange exchange) throws IOException {
        exchange.getResponseHeaders().add("Access-Control-Allow-Origin", "http://127.0.0.1:4500");
        exchange.getResponseHeaders().add("Access-Control-Allow-Methods", "GET, POST, DELETE, OPTIONS");
        exchange.getResponseHeaders().add("Access-Control-Allow-Headers", "Content-Type");
        exchange.sendResponseHeaders(204, -1); // 204 No Content
    }

    private void sendResponse(HttpExchange exchange, int code, String response) throws IOException {

        exchange.getResponseHeaders().add("Access-Control-Allow-Origin", "http://127.0.0.1:4500");
        exchange.getResponseHeaders().add("Access-Control-Allow-Methods", "GET, POST, DELETE, OPTIONS");
        exchange.getResponseHeaders().add("Access-Control-Allow-Headers", "Content-Type");
    

        exchange.sendResponseHeaders(code, response.length());
        try (OutputStream os = exchange.getResponseBody()) {
            os.write(response.getBytes());
        }
    }
}
