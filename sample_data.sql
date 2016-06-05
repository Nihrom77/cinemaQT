insert into genre (name) values('комедия');
insert into genre (name) values('фантастика');
insert into genre (name) values('боевик');
insert into genre (name) values('фэнтези');
insert into genre (name) values('мультфильм');
insert into genre (name) values('детектив');
insert into genre (name) values('ужасы');



insert into movies (name, duration, country, movie_company,age_restriction) 
values('Начало', 200, 'сша', 'luckas films', 18);

insert into movies (name, duration, country, movie_company,age_restriction) 
values ('Суперсемейка', 150, 'сша', 'pixar', 5);

insert into movies (name, duration, country, movie_company,age_restriction) 
values ('Лифт', 150, 'сша', '20 century fox', 16);

insert into movies (name, duration, country, movie_company,age_restriction) 
values ('Эффект бабочки 3', 150, 'сша', 'AfterDark Films', 18);

insert into movies (name, duration, country, movie_company,age_restriction) 
values ('Ким Пять-с-плюсом', 150, 'сша', 'Disney', 0);

insert into table_movie_genre (movie_id,genre_id) values(1,2)
insert into table_movie_genre (movie_id,genre_id) values(1,3)
insert into table_movie_genre (movie_id,genre_id) values(1,7)
insert into table_movie_genre (movie_id,genre_id) values(2,5)
insert into table_movie_genre (movie_id,genre_id) values(3,2)
insert into table_movie_genre (movie_id,genre_id) values(3,7)
insert into table_movie_genre (movie_id,genre_id) values(4,6)
insert into table_movie_genre (movie_id,genre_id) values(4,7)


insert into actor (name, second_name, country, birthdate) 
values ('Джонни', 'Депп', 'сша', '04.05.1990');

insert into actor (name, second_name, country, birthdate) 
values ('Саша', 'Коен', 'сша', '04.05.1990');

insert into participation (movie_id,actor_id,role) values
(1,1,'главный герой')
insert into participation (movie_id,actor_id,role) values
(1,2,'второстепенный герой')
insert into participation (movie_id,actor_id,role) values
(4,2,'нищий')

