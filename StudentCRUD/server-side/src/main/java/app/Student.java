package app;

import java.sql.Date;

public class Student {
    private Integer id;
    private String firstName;
    private String lastName;
    private String middleName;
    private Date birthDate;
    private String studentGroup;

    public Student(String firstName, String lastName, String middleName, Date birthDate, String studentGroup) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.middleName = middleName;
        this.birthDate = birthDate;
        this.studentGroup = studentGroup;
    }

    public Student(Integer id, String firstName, String lastName, String middleName, Date birthDate, String studentGroup) {
        this.id = id;
        this.firstName = firstName;
        this.lastName = lastName;
        this.middleName = middleName;
        this.birthDate = birthDate;
        this.studentGroup = studentGroup;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public String getMiddleName() {
        return middleName;
    }

    public void setMiddleName(String middleName) {
        this.middleName = middleName;
    }

    public Date getBirthDate() {
        return birthDate;
    }

    public void setBirthDate(Date birthDate) {
        this.birthDate = birthDate;
    }

    public String getStudentGroup() {
        return studentGroup;
    }

    public void setStudentGroup(String studentGroup) {
        this.studentGroup = studentGroup;
    }

    public String toJson() {
        return String.format(
            "{\"id\": %d, \"firstName\": \"%s\", \"lastName\": \"%s\", \"middleName\": \"%s\", \"birthDate\": \"%s\", \"studentGroup\": \"%s\"}",
            id, firstName, lastName, middleName, birthDate, studentGroup
        );
    }
}
