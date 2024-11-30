CREATE TABLE students (
  id_student SERIAL PRIMARY KEY,
  id_user INTEGER NOT NULL,
  id_career_year INTEGER,
  group_student INTEGER NOT NULL
);

CREATE TABLE profesors (
  id_profesor SERIAL PRIMARY KEY,
  id_deparment INTEGER NOT NULL,
  id_user INTEGER NOT NULL,
  category VARCHAR(50)
);

CREATE TABLE subjects (
  id_subject SERIAL PRIMARY KEY,
  id_profesor INTEGER,
  n_subject TEXT
);

CREATE TABLE faculties (
  id_faculty SERIAL PRIMARY KEY,
  n_faculty TEXT UNIQUE NOT NULL
);

CREATE TABLE careers (
  id_career SERIAL PRIMARY KEY,
  id_faculty INTEGER,
  n_career VARCHAR(50) NOT NULL,
  duration INTEGER NOT NULL
);

CREATE TABLE careers_years (
  id_career_year SERIAL PRIMARY KEY,
  id_career INTEGER,
  year INTEGER NOT NULL
);

CREATE TABLE careers_subjects (
  id_career_subject SERIAL PRIMARY KEY,
  id_subject INTEGER,
  id_career_year INTEGER
);

CREATE TABLE evaluations (
  id_evaluation SERIAL PRIMARY KEY,
  id_student INTEGER,
  id_subject INTEGER,
  calification INTEGER,
  evaluation_type VARCHAR(10),
  date_eval DATE
);

CREATE TABLE deparments (
  id_deparment SERIAL PRIMARY KEY,
  n_deparment TEXT UNIQUE
);

CREATE TABLE classes (
  id_classe SERIAL PRIMARY KEY,
  id_subject INTEGER,
  id_student INTEGER,
  cantidad_turnos INTEGER,
  date_class DATE,
  assis BOOLEAN
);

CREATE TABLE users (
  id_user SERIAL PRIMARY KEY,
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

CREATE TABLE users_images (
  id_user_image SERIAL PRIMARY KEY,
  directory_img TEXT NOT NULL,
  id_user INTEGER NOT NULL
);

ALTER TABLE subjects ADD FOREIGN KEY (id_profesor) REFERENCES profesors (id_profesor);
ALTER TABLE profesors ADD FOREIGN KEY (id_deparment) REFERENCES deparments (id_deparment);
ALTER TABLE evaluations ADD FOREIGN KEY (id_student) REFERENCES students (id_student);
ALTER TABLE profesors ADD FOREIGN KEY (id_user) REFERENCES users (id_user);
ALTER TABLE students ADD FOREIGN KEY (id_user) REFERENCES users (id_user);
ALTER TABLE personal_dates ADD FOREIGN KEY (CI_identity) REFERENCES users (CI_identity);
ALTER TABLE careers_subjects ADD FOREIGN KEY (id_subject) REFERENCES subjects (id_subject);
ALTER TABLE careers ADD FOREIGN KEY (id_faculty) REFERENCES faculties (id_faculty);
ALTER TABLE careers_years ADD FOREIGN KEY (id_career) REFERENCES careers (id_career);
ALTER TABLE careers_subjects ADD FOREIGN KEY (id_career_year) REFERENCES careers_years (id_career_year);
ALTER TABLE students ADD FOREIGN KEY (id_career_year) REFERENCES careers_years (id_career_year);
ALTER TABLE classes ADD FOREIGN KEY (id_subject) REFERENCES subjects (id_subject);
ALTER TABLE users_images ADD FOREIGN KEY (id_user) REFERENCES users (id_user);
ALTER TABLE evaluations ADD FOREIGN KEY (id_subject) REFERENCES subjects (id_subject);
ALTER TABLE classes ADD FOREIGN KEY (id_student) REFERENCES students (id_student);