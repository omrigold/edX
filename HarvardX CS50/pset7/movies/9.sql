select p.name, p.birth
from movies m
join stars s
  on m.id = s.movie_id
join people p
  on p.id = s.person_id
where m.year = 2004
group by p.id
order by p.birth;