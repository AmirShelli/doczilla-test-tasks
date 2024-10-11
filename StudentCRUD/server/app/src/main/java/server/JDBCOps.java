package server;

import java.sql.Connection;
import java.sql.Date;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

public class JDBCOps {

    public boolean insertStudent(String firstName, String lastName, String middleName, Date birthDate, String studentGroup) {
        String sql = "INSERT INTO student (first_name, last_name, middle_name, birth_date, student_group) VALUES (?, ?, ?, ?, ?)";

        try (Connection conn = JDBCUtils.getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, firstName);
            pstmt.setString(2, lastName);
            pstmt.setString(3, middleName);
            pstmt.setDate(4, birthDate);
            pstmt.setString(5, studentGroup);

            pstmt.executeUpdate();
            return true;

        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

    public List<String[]> getAllStudents() {
        String sql = "SELECT * FROM student";
        List<String[]> students = new ArrayList<>();

        try (Connection conn = JDBCUtils.getConnection();
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery(sql)) {

            while (rs.next()) {
                String[] studentData = new String[6];
                studentData[0] = String.valueOf(rs.getInt("id"));
                studentData[1] = rs.getString("first_name");
                studentData[2] = rs.getString("last_name");
                studentData[3] = rs.getString("middle_name");
                studentData[4] = rs.getDate("birth_date").toString();
                studentData[5] = rs.getString("student_group");

                students.add(studentData);
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
        return students;
    }

    public boolean deleteStudent(int id) {
        String sql = "DELETE FROM student WHERE id = ?";

        try (Connection conn = JDBCUtils.getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setInt(1, id);
            pstmt.executeUpdate();
            return true;

        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }
}
