CREATE DATABASE db_locadora; 

CREATE TABLE cliente( 
    id_cliente INTEGER , 
    nome CHARACTER(20) , 
    cpf CHARACTER(20) ,     
    celular CHARACTER(20),
    CONSTRAINT PK_cliente PRIMARY KEY (id_cliente,cpf)
); 

CREATE TABLE veiculo ( 
    id_veiculo INTEGER, 
    marca CHARACTER(20) , 
    modelo CHARACTER(20) , 
    placa CHARACTER(20) , 
    alugado CHARACTER(1)
);

CREATE TABLE aluguel ( 
    id_aluguel INTEGER, 
    id_cliente INTEGER , 
    id_veiculo INTEGER , 
    dt_saida DATE , 
    dt_retorno DATE,
);

 
ALTER TABLE aluguel ADD CONSTRAINT cliente_aluguel  
    FOREIGN KEY (id_cliente) REFERENCES cliente (id_cliente); 
 
ALTER TABLE aluguel ADD CONSTRAINT veiculo_aluguel  
    FOREIGN KEY (id_veiculo) REFERENCES veiculo (id_veiculo); 