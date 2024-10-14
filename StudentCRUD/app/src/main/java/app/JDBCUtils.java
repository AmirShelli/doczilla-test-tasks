package app;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class JDBCUtils {

    private static final String URL = System.getenv("DATASOURCE_URL");
    private static final String USER = System.getenv("DATASOURCE_USERNAME");
    private static final String PASSWORD = System.getenv("DATASOURCE_PASSWORD");

    public static Connection getConnection() throws SQLException {

        Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
        return connection;
    }

    public static void printSQLException(SQLException ex) {
        for (Throwable e : ex) {
            if (e instanceof SQLException sQLException) {
                e.printStackTrace(System.err);
                System.err.println("SQLState: " + sQLException.getSQLState());
                System.err.println("Error Code: " + sQLException.getErrorCode());
                System.err.println("Message: " + e.getMessage());
                Throwable t = ex.getCause();
                while (t != null) {
                    System.out.println("Cause: " + t);
                    t = t.getCause();
                }
            }
        }
    }
}
