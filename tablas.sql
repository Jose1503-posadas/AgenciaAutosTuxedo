CREATE TABLE Marcas (
    MarcaID INT PRIMARY KEY,
    Nombre VARCHAR(50),
    PaisOrigen VARCHAR(50)
);

INSERT INTO Marcas (MarcaID, Nombre, PaisOrigen)
VALUES(1, 'Honda', 'Japón');

INSERT INTO Marcas (MarcaID, Nombre, PaisOrigen)
VALUES(2, 'Toyota', 'Japón');

INSERT INTO Marcas (MarcaID, Nombre, PaisOrigen)
VALUES(3, 'Chevrolet', 'Estados Unidos');

SELECT * FROM marcas;
