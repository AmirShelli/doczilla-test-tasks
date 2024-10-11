package server;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.sql.Date;
import java.util.List;

import com.sun.net.httpserver.HttpServer;

public class App {

    public static void testJDBC() {
        StudentDAO operations = new StudentDAO();

        boolean isInserted = operations.insertStudent("first", "last", "middle", Date.valueOf("2000-01-01"), "A");
        if (isInserted) {
            List<String[]> students = operations.getAllStudents();
            System.out.println("List of all students:");
            for (String[] student : students) {
                System.out.println("ID: " + student[0] + ", First Name: " + student[1] + ", Last Name: " + student[2]
                        + ", Middle Name: " + student[3] + ", Birth Date: " + student[4] + ", Group: " + student[5]);
            }
        } else {
            System.out.println("Failed to insert student.");
        }

        boolean isDeleted = operations.deleteStudent(1);
        if (isDeleted) {
            List<String[]> students = operations.getAllStudents();
            System.out.println("List of all students:");
            for (String[] student : students) {
                System.out.println("ID: " + student[0] + ", First Name: " + student[1] + ", Last Name: " + student[2]
                        + ", Middle Name: " + student[3] + ", Birth Date: " + student[4] + ", Group: " + student[5]);
            }
        } else {
            System.out.println("Failed to delete student.");
        }
    }

    public static void main(String[] args) {
        try {
            HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
            server.createContext("/api/students", new StudentHandler());

            server.setExecutor(null);
            server.start();

            System.out.println("Server is running on port 8080");
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

}
