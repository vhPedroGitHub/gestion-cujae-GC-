CREATE TABLE students (
  id_student INTEGER GENERATED BY DEFAULT AS IDENTITY PRIMARY KEY,
  id_user INTEGER NOT NULL,
  id_career_year INTEGER,
  group_student INTEGER NOT NULL
);

CREATE TABLE profesors (
  id_profesor INTEGER GENERATED BY DEFAULT AS IDENTITY PRIMARY KEY,
  id_deparment INTEGER NOT NULL,
  id_user INTEGER NOT NULL,
  category VARCHAR(50)
);

CREATE TABLE subjects (
  id_subject INTEGER GENERATED BY DEFAULT AS IDENTITY PRIMARY KEY,
  id_profesor INTEGER,
  n_subject TEXT
);

CREATE TABLE faculties (
  id_faculty INTEGER GENERATED BY DEFAULT AS IDENTITY PRIMARY KEY,
  n_faculty TEXT UNIQUE NOT NULL
);

CREATE TABLE careers (
  id_career INTEGER GENERATED BY DEFAULT AS IDENTITY PRIMARY KEY,
  id_faculty INTEGER,
  n_career VARCHAR(50) NOT NULL,
  duration INTEGER NOT NULL
);

CREATE TABLE careers_years (
  id_career_year INTEGER GENERATED BY DEFAULT AS IDENTITY PRIMARY KEY,
  id_career INTEGER,
  year INTEGER NOT NULL
);

CREATE TABLE careers_subjects (
  id_career_subject INTEGER GENERATED BY DEFAULT AS IDENTITY PRIMARY KEY,
  id_subject INTEGER,
  id_career_year INTEGER
);

CREATE TABLE evaluations (
  id_evaluation INTEGER GENERATED BY DEFAULT AS IDENTITY PRIMARY KEY,
  id_classe INTEGER,
  id_student INTEGER,
  calification INTEGER,
  evaluation_type VARCHAR(10)
);

CREATE TABLE deparments (
  id_deparment INTEGER GENERATED BY DEFAULT AS IDENTITY PRIMARY KEY,
  n_deparment TEXT UNIQUE
);

CREATE TABLE classes (
  id_classe INTEGER GENERATED BY DEFAULT AS IDENTITY PRIMARY KEY,
  id_career_subject INTEGER,
  cantidad_turnos INTEGER,
  date_class TIMESTAMP
);

CREATE TABLE assistances (
  id_assistance INTEGER GENERATED BY DEFAULT AS IDENTITY PRIMARY KEY,
  id_classe INTEGER,
  id_student INTEGER,
  assis BOOLEAN
);

CREATE TABLE users (
  id_user INTEGER GENERATED BY DEFAULT AS IDENTITY PRIMARY KEY,
  CI_identity VARCHAR(11) UNIQUE,
  user_name VARCHAR(15) NOT NULL,
  password_user VARCHAR(60) NOT NULL,
  user_type INTEGER NOT NULL
);

CREATE TABLE personal_dates (
  CI_identity VARCHAR(11) PRIMARY KEY,
  person_n VARCHAR(20) NOT NULL,
  last_name_1 VARCHAR(20) NOT NULL,
  last_name_2 VARCHAR(20) NOT NULL
);

CREATE TABLE students_images (
  id_student_image INTEGER PRIMARY KEY,
  directory_img TEXT NOT NULL,
  id_student INTEGER NOT NULL
);

ALTER TABLE subjects ADD FOREIGN KEY (id_profesor) REFERENCES profesors (id_profesor);
ALTER TABLE profesors ADD FOREIGN KEY (id_deparment) REFERENCES deparments (id_deparment);
ALTER TABLE assistances ADD FOREIGN KEY (id_classe) REFERENCES classes (id_classe);
ALTER TABLE assistances ADD FOREIGN KEY (id_student) REFERENCES students (id_student);
ALTER TABLE evaluations ADD FOREIGN KEY (id_classe) REFERENCES classes (id_classe);
ALTER TABLE evaluations ADD FOREIGN KEY (id_student) REFERENCES students (id_student);
ALTER TABLE profesors ADD FOREIGN KEY (id_user) REFERENCES users (id_user);
ALTER TABLE students ADD FOREIGN KEY (id_user) REFERENCES users (id_user);
ALTER TABLE personal_dates ADD FOREIGN KEY (CI_identity) REFERENCES users (CI_identity);
ALTER TABLE careers_subjects ADD FOREIGN KEY (id_subject) REFERENCES subjects (id_subject);
ALTER TABLE classes ADD FOREIGN KEY (id_career_subject) REFERENCES careers_subjects (id_career_subject);
ALTER TABLE students_images ADD FOREIGN KEY (id_student) REFERENCES students (id_student);
ALTER TABLE careers ADD FOREIGN KEY (id_faculty) REFERENCES faculties (id_faculty);
ALTER TABLE careers_years ADD FOREIGN KEY (id_career) REFERENCES careers (id_career);
ALTER TABLE careers_subjects ADD FOREIGN KEY (id_career_year) REFERENCES careers_years (id_career_year);
ALTER TABLE students ADD FOREIGN KEY (id_career_year) REFERENCES careers_years (id_career_year);