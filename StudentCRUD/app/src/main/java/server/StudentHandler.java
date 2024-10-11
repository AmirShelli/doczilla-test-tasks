package server;

import java.io.IOException;
import java.io.OutputStream;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;

public class StudentHandler implements HttpHandler {

    @Override
    public void handle(HttpExchange exchange) throws IOException {

        String method = exchange.getRequestMethod();

        if("GET".equalsIgnoreCase(method))
            getAllStudents(exchange);
        if("POST".equalsIgnoreCase(method))
            createStudent(exchange);
        if("DELETE".equalsIgnoreCase(method));
            deleteStudent(exchange);


        String response = "Hello, this is a simple HTTP server response!";
        exchange.sendResponseHeaders(200, response.length());
        OutputStream os = exchange.getResponseBody();
        os.write(response.getBytes());
        os.close();
    }

    private void createStudent(HttpExchange exchange) {

    }
    private void deleteStudent(HttpExchange exchange) {

    }
    private void getAllStudents(HttpExchange exchange) {
        StudentDAO dao = new StudentDAO();
        dao.getAllStudents();

        
    }

}
