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

CREATE TABLE Autos (
    AutoID INT PRIMARY KEY,
    MarcaID INT,
    Modelo VARCHAR(50),
    Anio INT,
    Precio DECIMAL(10, 2),
    Stock INT,
    FOREIGN KEY (MarcaID) REFERENCES Marcas(MarcaID)
);

-- Insertar datos en la tabla Autos
INSERT INTO Autos (AutoID, MarcaID, Modelo, Anio, Precio, Stock)
VALUES
    (1, 1, 'Civic', 2022, 25000.00, 10);

INSERT INTO Autos (AutoID, MarcaID, Modelo, Anio, Precio, Stock)
VALUES
    (2, 2, 'Camry', 2023, 28000.00, 8);

INSERT INTO Autos (AutoID, MarcaID, Modelo, Anio, Precio, Stock)
VALUES
    (3, 1, 'Accord', 2022, 27000.00, 12);

CREATE TABLE Ventas (
    VentaID NUMERIC,
    ClienteID NUMERIC,
    AutoID NUMERIC,
    Precio DECIMAL(10, 2)
);

-- Insertar datos en la tabla Ventas
INSERT INTO Ventas (VentaID, ClienteID, AutoID, Precio)
VALUES
    (1, 1, 1, 25000.00);

INSERT INTO Ventas (VentaID, ClienteID, AutoID, Precio)
VALUES
    (2, 2, 2, 28000.00);

INSERT INTO Ventas (VentaID, ClienteID, AutoID, Precio)
VALUES
    (3, 3, 3, 27000.00);
    
SELECT * FROM ventas;

SELECT * FROM clientes;

INSERT INTO Clientes (ClienteID, Nombre, Apellido, Direccion, Telefono)
VALUES
    (1, 'Juan', 'Perez', 'Calle 123, Ciudad', '555-1234');

INSERT INTO Clientes (ClienteID, Nombre, Apellido, Direccion, Telefono)
VALUES
    (2, 'Maria', 'Gomez', 'Avenida 456, Ciudad', '555-5678');

INSERT INTO Clientes (ClienteID, Nombre, Apellido, Direccion, Telefono)
VALUES
    (3, 'Carlos', 'Rodriguez', 'Plaza 789, Ciudad', '555-9012');
