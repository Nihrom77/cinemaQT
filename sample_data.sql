insert into genre (name) values('�������');
insert into genre (name) values('����������');
insert into genre (name) values('������');
insert into genre (name) values('�������');
insert into genre (name) values('����������');
insert into genre (name) values('��������');
insert into genre (name) values('�����');



insert into movies (name, duration, country, movie_company,age_restriction) 
values('������', 200, '���', 'luckas films', 18);

insert into movies (name, duration, country, movie_company,age_restriction) 
values ('������������', 150, '���', 'pixar', 5);

insert into movies (name, duration, country, movie_company,age_restriction) 
values ('����', 150, '���', '20 century fox', 16);

insert into movies (name, duration, country, movie_company,age_restriction) 
values ('������ ������� 3', 150, '���', 'AfterDark Films', 18);

insert into movies (name, duration, country, movie_company,age_restriction) 
values ('��� ����-�-������', 150, '���', 'Disney', 0);

insert into table_movie_genre (movie_id,genre_id) values(1,2)
insert into table_movie_genre (movie_id,genre_id) values(1,3)
insert into table_movie_genre (movie_id,genre_id) values(1,7)
insert into table_movie_genre (movie_id,genre_id) values(2,5)
insert into table_movie_genre (movie_id,genre_id) values(3,2)
insert into table_movie_genre (movie_id,genre_id) values(3,7)
insert into table_movie_genre (movie_id,genre_id) values(4,6)
insert into table_movie_genre (movie_id,genre_id) values(4,7)


insert into actor (name, second_name, country, birthdate) 
values ('������', '����', '���', '04.05.1990');

insert into actor (name, second_name, country, birthdate) 
values ('����', '����', '���', '04.05.1990');

insert into participation (movie_id,actor_id,role) values
(1,1,'������� �����')
insert into participation (movie_id,actor_id,role) values
(1,2,'�������������� �����')
insert into participation (movie_id,actor_id,role) values
(4,2,'�����')

