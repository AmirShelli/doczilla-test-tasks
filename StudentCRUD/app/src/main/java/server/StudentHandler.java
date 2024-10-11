package server;

import java.io.IOException;
import java.io.OutputStream;
import java.util.List;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;

public class StudentHandler implements HttpHandler {

    @Override
    public void handle(HttpExchange exchange) throws IOException {

        String method = exchange.getRequestMethod();
        String path = exchange.getRequestURI().getPath();
        String params = path.substring("/api/students/".length());

        if ("GET".equalsIgnoreCase(method)) {
            getAllStudents(exchange);
        } else if ("POST".equalsIgnoreCase(method) && !params.isEmpty()) {
            createStudent(exchange);
        } else if ("DELETE".equalsIgnoreCase(method) && !params.isEmpty()) {
            deleteStudent(exchange);
        } else {
            sendResponse(exchange, 405, "Method Not Allowed");
        }
    }

    private void createStudent(HttpExchange exchange) {

    }

    private void deleteStudent(HttpExchange exchange) {

    }

    private void getAllStudents(HttpExchange exchange) throws IOException {
        StudentDAO dao = new StudentDAO();
        List<Student> students = dao.getAllStudents();

        StringBuilder sb = new StringBuilder();

        for (Student student : students) {
            sb.append(student.toJson()).append("\n");
        }

        sendResponse(exchange, 200, sb.toString());
    }

    private void sendResponse(HttpExchange exchange, int code, String response) throws IOException {
        exchange.sendResponseHeaders(code, response.length());
        OutputStream os = exchange.getResponseBody();
        os.write(response.getBytes());
        os.close();
    }
}
