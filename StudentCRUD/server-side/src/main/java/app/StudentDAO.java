package app;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class StudentDAO {

    public boolean createStudent(Student student) {
        String sql = "INSERT INTO student (first_name, last_name, middle_name, birth_date, student_group) VALUES (?, ?, ?, ?, ?)";
        String sql1 = "SELECT * FROM student";


        try (Connection conn = JDBCUtils.getConnection(); PreparedStatement pstmt = conn.prepareStatement(sql); PreparedStatement test = conn.prepareStatement(sql1);) {

            pstmt.setString(1, student.getFirstName());
            pstmt.setString(2, student.getLastName());
            pstmt.setString(3, student.getMiddleName());
            pstmt.setDate(4, student.getBirthDate());
            pstmt.setString(5, student.getStudentGroup());

            pstmt.executeUpdate();
            return true;

        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

    public List<Student> getAllStudents() {
        String sql = "SELECT * FROM student";
        List<Student> students = new ArrayList<>();

        try (Connection conn = JDBCUtils.getConnection(); PreparedStatement pstmt = conn.prepareStatement(sql)) {
            ResultSet resultSet = pstmt.executeQuery();

            while (resultSet.next()) {
                students.add(new Student(
                        resultSet.getInt("id"),
                        resultSet.getString("first_name"),
                        resultSet.getString("last_name"),
                        resultSet.getString("middle_name"),
                        resultSet.getDate("birth_date"),
                        resultSet.getString("student_group")
                ));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return students;
    }

    public boolean deleteStudent(int id) {
        String sql = "DELETE FROM student WHERE id = ?";

        try (Connection conn = JDBCUtils.getConnection(); PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setInt(1, id);
            return pstmt.executeUpdate() > 0;

        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }
}
