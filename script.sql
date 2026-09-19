CREATE DATABASE oficina;

CREATE TABLE cliente (
    id_cliente INTEGER,
    nome CHARACTER(20),
    CONSTRAINT pk_cliente PRIMARY KEY (id_cliente)
);

CREATE TABLE veiculo (
    id_veiculo INTEGER,
    marca CHARACTER(20),
    modelo CHARACTER(20),
    dono CHARACTER(20),
    placa CHARACTER(20),
    combustivel CHARACTER(1),
    ano INTEGER,
    chassi CHARACTER(20),
    CONSTRAINT pk_veiculo PRIMARY KEY (id_veiculo)
);

CREATE TABLE aluguel (
    id_aluguel INTEGER,
    id_cliente INTEGER,
    id_veiculo INTEGER,
    dt_saida DATE,
    dt_retorno DATE
);

ALTER TABLE aluguel ADD CONSTRAINT cliente_aluguel 
    FOREIGN KEY (id_cliente) REFERENCES cliente (id_cliente);

ALTER TABLE aluguel ADD CONSTRAINT veiculo_aluguel
    FOREIGN KEY (id_veiculo) REFERENCES veiculo (id_veiculo);

CREATE TABLE servico (
    id_servico INTEGER,
    descricao CHARACTER(20),
    valor FLOAT,
    CONSTRAINT pk_servico PRIMARY KEY (id_servico)
);

CREATE TABLE peca (
    id_peca INTEGER,
    descricao CHARACTER(20),
    valor FLOAT,
    estoque INTEGER,
    CONSTRAINT pk_peca PRIMARY KEY (id_peca)
);

CREATE TABLE ordem_servico (
    id_os INTEGER,
    id_veiculo INTEGER,
    km_entrada INTEGER,
    data_entrada DATE,
    hora_entrada CHARACTER(20),
    data_saida DATE,
    hora_saida CHARACTER(20),
    valor_total FLOAT,
    CONSTRAINT pk_ordem_servico PRIMARY KEY (id_os),
    CONSTRAINT fk_os_veiculo FOREIGN KEY (id_veiculo)
    REFERENCES veiculo (id_veiculo)
);

CREATE TABLE os_servico (
    id_os INTEGER,
    id_servico INTEGER,
    valor FLOAT,
    CONSTRAINT pk_os_servico PRIMARY KEY (id_os, id_servico),
    CONSTRAINT fk_ossrv_os FOREIGN KEY (id_os)
    REFERENCES ordem_servico (id_os),
    CONSTRAINT fk_ossrv_servico FOREIGN KEY (id_servico)
    REFERENCES servico (id_servico)
);

CREATE TABLE os_peca (
    id_os INTEGER,
    id_peca INTEGER,
    quantidade INTEGER,
    valor FLOAT,
    CONSTRAINT pk_ospeca PRIMARY KEY (id_os, id_peca),
    CONSTRAINT fk_ospeca_os FOREIGN KEY (id_os)
    REFERENCES ordem_servico (id_os),
    CONSTRAINT fk_ospeca_peca FOREIGN KEY (id_peca)
    REFERENCES peca (id_peca)
);

INSERT INTO cliente(id_cliente, nome) VALUES (1, 'teste');

INSERT INTO veiculo(id_veiculo, marca, modelo, dono, placa) VALUES (1, 'porsche', '911', 'eu', 'FZR');

INSERT INTO veiculo(id_veiculo, marca, modelo, dono, placa) VALUES (2, 'porsche', '911', 'eu', 'FZR');