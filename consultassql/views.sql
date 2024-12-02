-- DROP VIEW 
DROP VIEW view_profesor_subject;
DROP VIEW view_subject_career;  
DROP VIEW view_student_career;
DROP VIEW view_info_pers_student;
DROP VIEW view_info_pers_profesor;

-- id_student, id_user, nombre, apellido, grupo y carne de identidad
-- datos personales de un estudiante
CREATE VIEW view_info_pers_student AS 
SELECT 
    s.id_student, 
    u.id_user, 
    pd.person_n, 
    pd.last_name_1,
    pd.last_name_2, 
    s.group_student, 
    u.CI_identity, 
	directory_img
FROM 
    students s
INNER JOIN 
    users u ON s.id_user = u.id_user
INNER JOIN 
    personal_dates pd ON pd.CI_identity = u.CI_identity
LEFT JOIN 
	users_images um ON um.id_user = u.id_user;

-- Para obtener los datos personales de los profesores
CREATE VIEW view_info_pers_profesor AS
SELECT 
    pr.id_profesor, 
    u.id_user, 
    pd.person_n, 
    pd.last_name_1,
    pd.last_name_2, 
	n_deparment,
	category,
    u.CI_identity, 
	directory_img
FROM 
    profesors pr
INNER JOIN 
    users u ON pr.id_user = u.id_user
INNER JOIN 
    personal_dates pd ON pd.CI_identity = u.CI_identity
INNER JOIN 
    deparments d ON d.id_deparment = pr.id_deparment
LEFT JOIN 
	users_images um ON um.id_user = u.id_user;

-- Obtenemos los datos de un profesor y de las asignaturas que el da
CREATE VIEW view_profesor_subject AS
SELECT sb.id_subject, pr.id_profesor, person_n, last_name_1, last_name_2, n_subject  FROM profesors pr
INNER JOIN 
	subjects sb ON sb.id_profesor = pr.id_profesor
INNER JOIN 
	view_info_pers_profesor vp ON vp.id_profesor=pr.id_profesor;

-- Para obtener cada anno de la carrera con su respectivo nombre
CREATE VIEW view_subject_career AS
SELECT cy.id_career_year, s.id_subject, crr.n_career, cy.year FROM subjects s
INNER JOIN 
	careers_subjects cs ON cs.id_subject = s.id_subject
INNER JOIN
	careers_years cy ON cy.id_career_year = cs.id_career_year
INNER JOIN
	careers crr ON crr.id_career = cy.id_career
ORDER BY cy.id_career_year;

-- Obtenemos los estudiantes con su respectiva carrera estudiada
CREATE VIEW view_student_career AS
SELECT s.id_student, s.id_user, cy.id_career_year, person_n, 
		last_name_1, last_name_2, CI_identity, vs.group_student, directory_img FROM students s
INNER JOIN
	careers_years cy ON s.id_career_year = cy.id_career_year
INNER JOIN 
	view_info_pers_student vs ON vs.id_student = s.id_student
GROUP BY s.id_student;

CREATE VIEW view_student_assis AS
SELECT sw.id_student,
    sw.id_user,
    sw.person_n,
    sw.last_name_1,
    sw.last_name_2,
    sw.group_student,
    sw.ci_identity,
    sw.directory_img,
	id_subject,
	id_classe,
	assis,
	cantidad_turnos
	FROM view_info_pers_student sw
INNER JOIN classes cl ON sw.id_student = cl.id_student