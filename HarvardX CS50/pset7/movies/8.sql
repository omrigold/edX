select p.name
from movies m
join stars s
  on m.id = s.movie_id
join people p
  on p.id = s.person_id
where m.title = "Toy Story";