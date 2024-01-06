use events;

CREATE TABLE event (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    location TEXT NOT NULL,
    date INTEGER NOT NULL,
    img TEXT NOT NULL,
    imgDesc TEXT NOT NULL
);

CREATE TABLE details (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    event_id INTEGER NOT NULL,
    fullName TEXT NOT NULL,
    time TEXT NOT NULL
);

CREATE TABLE description (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    event_id INT NOT NULL,
    content VARCHAR(1000) NOT NULL
);

CREATE TABLE coordinates (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    event_id INTEGER NOT NULL,
    latitude REAL NOT NULL,
    longitude REAL NOT NULL
);

INSERT INTO coordinates (event_id, latitude, longitude) VALUES 
(1, 51.109, 17.032);

INSERT INTO event (id, name, location, date, img, imgDesc) VALUES 
(
    1,
    'Jarmark Świętojański...', 
    'Wrocław, Rynek', 
    '2023-06-19', 
    'https://www.wroclaw.pl/go/download/img-d4d124c42df7bd082e49877f9a18dac0/jarmark-swietojanski-wroclaw-2021-16-jpg.jpg', 
    'Jarmark Świętojański'
);

UPDATE event set img = 'https://www.wroclaw.pl/go/download/img-d4d124c42df7bd082e49877f9a18dac0/jarmark-swietojanski-wroclaw-2021-16-jpg.jpg' where id = 1;

INSERT INTO details (event_id, fullName, time) VALUES 
(
    1, 
    'Jarmark Świętojański', 
    '12:00:00'
);

INSERT INTO description (event_id, content) VALUES 
(1,'Jarmark Świętojański 2023 odbędzie się w terminie od 19 maja do 27 czerwca. Stoiska otwarte będą od godz. 10.00 do 21.00, sprzedaż artykułów będzie prowadzone również online na pojawi.pl'),
(1,'Jarmark Świętojański odbędzie się na wrocławskim Rynku – w obszarze wokół Pręgierza, ulicy Oławskiej od ulicy Szewskiej do Rynku i Świdnickiej od przejścia podziemnego do Rynku.'),
(1,'Sprzedaż na Jarmarku Świętojańskim odbywać się będzie wyłącznie z domków drewnianych. Nie ma możliwości prowadzenia sprzedaży z namiotów, foodtrucków lub ustawiania indywidualnych ekspozycji i prowadzenia sprzedaży poza domkiem.'),
(1,'Artykuły przemysłowe, rękodzieło i rzemiosło – artystyczne wyroby własne, dekoracje i ozdoby, ceramika, biżuteria, mydła i kosmetyki naturalne, ręcznie szyte zabawki z naturalnych materiałów, wyroby regionalne (w tym góralskie), kubki pamiątkowe z nadrukiem, pamiątki, wyroby ze szkła, świece, metaloplastyka, galanteria, torby, odzież artystyczna.'),
(1,'Artykuły spożywcze – regionalne sery i wędliny, pieczywo i wypieki, konfitury, miody, nalewki, wyroby czekoladowe i słodycze, zioła i przyprawy, kawy i herbaty, produkty naturalne i wegańskie.');

TableInfo{
    name='Event', columns={name=Column{name='name', type='TEXT', affinity='2', notNull=true, primaryKeyPosition=0, defaultValue='undefined'}, date=Column{name='date', type='INTEGER', affinity='3', notNull=true, primaryKeyPosition=0, defaultValue='undefined'}, location=Column{name='location', type='TEXT', affinity='2', notNull=true, primaryKeyPosition=0, defaultValue='undefined'}, img=Column{name='img', type='TEXT', affinity='2', notNull=true, primaryKeyPosition=0, defaultValue='undefined'}, id=Column{name='id', type='INTEGER', affinity='3', notNull=true, primaryKeyPosition=1, defaultValue='undefined'}, imgDesc=Column{name='imgDesc', type='TEXT', affinity='2', notNull=true, primaryKeyPosition=0, defaultValue='undefined'}}, foreignKeys=[], indices=[]}

TableInfo{
    name='Event', columns={
        id=Column{name='id', type='INTEGER', affinity='3', notNull=false, primaryKeyPosition=1, defaultValue='undefined'}, name=Column{name='name', type='TEXT', affinity='2', notNull=true, primaryKeyPosition=0, defaultValue='undefined'}, location=Column{name='location', type='TEXT', affinity='2', notNull=true, primaryKeyPosition=0, defaultValue='undefined'}, date=Column{name='date', type='INTEGER', affinity='3', notNull=true, primaryKeyPosition=0, defaultValue='undefined'}, img=Column{name='img', type='TEXT', affinity='2', notNull=true, primaryKeyPosition=0, defaultValue='undefined'}, imgDesc=Column{name='imgDesc', type='TEXT', affinity='2', notNull=true, primaryKeyPosition=0, defaultValue='undefined'}}, foreignKeys=[], indices=[]}
        