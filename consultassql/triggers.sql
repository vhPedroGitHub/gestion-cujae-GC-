-- valida la entra de dato de los usuarios

CREATE OR REPLACE FUNCTION validate_user_insert() 
RETURNS TRIGGER AS $$
BEGIN
    -- Validar CI_identity: debe ser NULL o tener exactamente 11 caracteres numéricos
    IF NEW.CI_identity IS NOT NULL AND (LENGTH(NEW.CI_identity) != 11 OR NEW.CI_identity !~ '^[0-9]+$') THEN
        RAISE EXCEPTION 'CI_identity debe ser NULL o tener exactamente 11 dígitos numéricos';
    END IF;

    -- Validar user_type: debe ser un número entre 1 y 3
    IF NEW.user_type < 1 OR NEW.user_type > 3 THEN
        RAISE EXCEPTION 'user_type debe ser un número entre 1 y 3';
    END IF;

    RETURN NEW; -- Permitir la inserción si las validaciones son correctas
END;
$$
LANGUAGE plpgsql;

CREATE TRIGGER validate_user_before_insert
BEFORE INSERT ON users
FOR EACH ROW EXECUTE PROCEDURE validate_user_insert();

-- verifica que no se le vuelva asiganar a una carrera una asignatura que ya tiene asignada
CREATE OR REPLACE FUNCTION validate_unique_career_subject_insert() 
RETURNS TRIGGER AS $$
BEGIN
    -- Verificar si ya existe un registro con los mismos valores
    IF EXISTS (
        SELECT 1 FROM careers_subjects 
        WHERE id_subject = NEW.id_subject 
          AND id_career_year = NEW.id_career_year
    ) THEN
        RAISE EXCEPTION 'El registro con id_subject = % y id_career_year = % ya existe en la tabla careers_subjects', NEW.id_subject, NEW.id_career_year;
    END IF;

    RETURN NEW; -- Permitir la inserción si no hay duplicados
END;
$$
LANGUAGE plpgsql;

CREATE TRIGGER validate_career_subject_before_insert
BEFORE INSERT ON careers_subjects
FOR EACH ROW EXECUTE PROCEDURE validate_unique_career_subject_insert();

-- verifica que no se este actualizando ni insertando un registro el cual ya tiene datos existentes
CREATE OR REPLACE FUNCTION validate_unique_subject() 
RETURNS TRIGGER AS $$
BEGIN
    -- Verificar si ya existe un registro con los mismos valores
    IF EXISTS (
        SELECT 1 FROM subjects 
        WHERE id_profesor = NEW.id_profesor 
          AND n_subject = NEW.n_subject
          AND id_subject <> COALESCE(OLD.id_subject, 0) -- Asegurarse de no comparar con el mismo registro en caso de UPDATE
    ) THEN
        RAISE EXCEPTION 'El registro con id_profesor = % y n_subject = % ya existe en la tabla subjects', NEW.id_profesor, NEW.n_subject;
    END IF;

    RETURN NEW; -- Permitir la inserción o actualización si no hay duplicados
END;
$$
LANGUAGE plpgsql;

CREATE TRIGGER validate_subject_before_insert_update
BEFORE INSERT OR UPDATE ON subjects
FOR EACH ROW EXECUTE PROCEDURE validate_unique_subject();