select p.name
from movies m
join directors d
  on m.id = d.movie_id
join people p
  on p.id = d.person_id
join ratings r
  on r.movie_id = m.id
where r.rating >= 9.0
group by p.id;