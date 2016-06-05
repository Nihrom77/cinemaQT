create table if not exists genre(
  genre_id serial primary key,
  name varchar(100) not null
);

create table if not exists movies(
movie_id serial primary key,
name varchar(100),
duration integer,
country varchar(30),
movie_company varchar(100),
age_restriction integer
);

create table if not exists table_movie_genre(
  genre_id integer references genre(genre_id),
  movie_id integer references movies(movie_id)
);


create table if not exists actor(
  actor_id serial primary key,
  name varchar(20) not null,
  second_name varchar(20) not null,
  country varchar(20) not null,
  birthdate date not null
);

create table if not exists participation(
  movie_id integer references movies(movie_id),
  actor_id integer references actor(actor_id),
  role varchar(20) not null
);

create table if not exists price(
  price_id serial primary key,
  type_of_time varchar(20) not null,
  cost integer not null
);

create table if not exists type(
  type_id serial primary key,
  name varchar(20) not null,
  price_id integer references price(price_id)
);

create table if not exists seat(
  seat_id serial primary key,
  row integer not null,
  number_seat integer not null,
  type_id integer references type(type_id)
);

create table if not exists hall(
  hall_id serial primary key,
  name varchar(20) not null,
  capacity integer not null
);


create table if not exists seat_hall(
  hall_id integer references hall(hall_id),
  seat_id integer references seat(seat_id)
);


create table if not exists seance(
  seance_id serial primary key,
  movie varchar(20) not null,
  hall integer not null,
  seance_time timestamp with time zone
);

create table if not exists booking(
  booking_id serial primary key,
  seance_id integer references seance(seance_id),
  seat_id integer references seat(seat_id)
);


