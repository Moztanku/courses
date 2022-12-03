-- 1)
show tables;
-- 2)
select title from film where length > 120;
-- 3)
select title from film where rating='G' order by length limit 4;
-- 4)
select title,name from film join language on film.language_id=language.language_id where description like '%Drama%';
-- 5)
select title from film join film_category on film.film_id=film_category.film_id where description like '%Documentary%' and category_id=8;
-- 6)
select title from film join film_category on film.film_id=film_category.film_id where category_id=3 and rating<>'G';
-- 7)
select rating,count(*) from film group by rating;
-- 8)
create view help1 as select film_id from rental join inventory on rental.inventory_id=inventory.inventory_id where rental_date between '2005-05-31' and '2005-06-15';
select distinct title from film join help1 on film.film_id=help1.film_id order by title;
-- 9)
create view deletedScenesFilmIds as select film_id from film where special_features like '%deleted scenes%';
create view deletedScenesActorsIds as select distinct actor_id from film_actor where film_id in(select film_id from deletedScenesFilmIds);
select first_name,last_name from actor where actor_id in(select actor_id from deletedScenesActorsIds);
-- 10)
create view customerIdDifferentStaff as select p.customer_id from payment p join rental r on p.rental_id=r.rental_id where p.staff_id<>r.staff_id;
select first_name,last_name from customer where customer_id in(select customer_id from customerIdDifferentStaff);
-- 11)
create view marysmithcount as select count(*) as count from rental where customer_id=(select customer_id from customer where email='MARY.SMITH@sakilacustomer.org');
create view customermorefilmsthanmarysmith as select customer_id from rental group by customer_id having count(*)>(select count from marysmithcount);
select first_name,last_name from customer where customer_id in(select customer_id from customermorefilmsthanmarysmith);
-- 12)
create view actor_pair as (select count(*) as count,a1.actor_id as a1_id, a2.actor_id as a2_id from film_actor a1 join film_actor a2 on a1.film_id=a2.film_id where a1.actor_id > a2.actor_id group by a1.actor_id,a2.actor_id having count > 1);
select concat(a1.first_name," ",a1.last_name) as name,concat(a1.first_name," ",a2.last_name) as name from actor a1 join actor a2 where (a1.actor_id,a2.actor_id) in (select a1_id,a2_id from actor_pair);
-- 13)
create view actorsIdMovieTitleS as select distinct actor_id from film_actor where (select title from film where film.film_id=film_actor.film_id) like 'C%';
select first_name,last_name from actor where actor_id not in(select actor_id from actorsIdMovieTitleS);
-- 14)
create view actionMovie as select actor_id,count(*) as actionFilms from film_actor where (select category_id from film_category where film_actor.film_id=film_category.film_id)=1 group by actor_id;
create view horrorMovie as select actor_id,count(*) as actionFilms from film_actor where (select category_id from film_category where film_actor.film_id=film_category.film_id)=11 group by actor_id;
create view actionMoviesActors as select am.actor_id,am.actionFilms as action,ifnull(hm.actionFilms,0) as horror from actionMovie am left join horrorMovie hm on am.actor_id=hm.actor_id having action>horror;
select first_name,last_name from actor where actor_id in(select actor_id from actionMoviesActors);
-- 15)
create view averageOnDate as select AVG(amount) as amount from payment where DATE(payment_date)='2005-07-30';
create view amountCustomer as select customer_id,AVG(amount) as amount from payment group by customer_id having amount>(select amount from averageOnDate);
select first_name,last_name from customer where customer_id in(select customer_id from amountCustomer);
-- 16)
update film set language_id=2 where film_id=996;
-- 17)
insert into language(language_id,name,last_update) values(7,'Spanish',Now());
create view edChase as select actor_id,CONCAT(first_name,' ',last_name) as name from actor having name='ED CHASE';
create view edChaseFilms as select film_id from film_actor where actor_id=(select actor_id from edChase);
update film set language_id=7 where film_id in(select film_id from edChaseFilms);
-- 18)
update language set films_no=(select count(*) from film where film.language_id=language.language_id);
-- 19)
alter table film drop column release_year;
