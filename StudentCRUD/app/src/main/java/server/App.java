package server;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.sql.Date;
import java.util.List;

import com.sun.net.httpserver.HttpServer;

public class App {

    public static void testJDBC() {
        StudentDAO operations = new StudentDAO();

        boolean isInserted = operations.createStudent(new Student(1, "first", "last", "middle", Date.valueOf("2000-01-01"), "A"));
        if (isInserted) {
            List<Student> students = operations.getAllStudents();
            System.out.println("List of all students:");
            for (Student student : students) {
                System.out.println("ID: " + student.getId() + ", First Name: " + student.getFirstName() + ", Last Name: " + student.getLastName()
                        + ", Middle Name: " + student.getMiddleName() + "Birth Date: " + student.getBirthDate() + ", Group: " + student.getStudentGroup());
            }
        } else {
            System.out.println("Failed to insert student.");
        }

        boolean isDeleted = operations.deleteStudent(1);
        if (isDeleted) {
            List<Student> students = operations.getAllStudents();
            System.out.println("List of all students:");
            for (Student student : students) {
                System.out.println("ID: " + student.getId() + ", First Name: " + student.getFirstName() + ", Last Name: " + student.getLastName()
                        + ", Middle Name: " + student.getMiddleName() + "Birth Date: " + student.getBirthDate() + ", Group: " + student.getStudentGroup());
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
