CREATE TABLE IF NOT EXISTS student (
    id SERIAL PRIMARY KEY,
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50) NOT NULL,
    middle_name VARCHAR(50),
    birth_date DATE NOT NULL,
    student_group VARCHAR(50) NOT NULL
);

INSERT INTO student (first_name, last_name, middle_name, birth_date, student_group) VALUES
('John', 'Doe', 'A.', '2000-05-15', 'Computer Science'),
('Jane', 'Smith', NULL, '1999-08-22', 'Mathematics'),
('Alice', 'Johnson', 'B.', '2001-12-03', 'Physics'),
('Bob', 'Williams', 'C.', '2000-03-30', 'Chemistry'),
('Emily', 'Davis', NULL, '1998-07-19', 'Biology'),
('Michael', 'Brown', 'D.', '1999-11-11', 'Engineering'),
('Sophia', 'Miller', 'E.', '2002-01-25', 'Literature'),
('Daniel', 'Wilson', NULL, '2001-04-17', 'History'),
('Olivia', 'Moore', 'F.', '1998-09-05', 'Philosophy'),
('James', 'Taylor', 'G.', '2000-02-28', 'Economics');