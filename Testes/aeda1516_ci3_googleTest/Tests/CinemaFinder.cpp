/*
 * CinemaFinder.cpp
 */

#include "CinemaFinder.h"
#include "Cinema.h"
#include "Film.h"
#include <algorithm>

CinemaFinder::CinemaFinder() { }

CinemaFinder::~CinemaFinder() { }

void CinemaFinder::addFilm(Film *f1) {
	FilmPtr fp1;
	fp1.film = f1;
	films.insert(fp1);
}

void CinemaFinder::addCinema(const Cinema &c1)
{ cinemas.push(c1); }

tabHFilm CinemaFinder::getFilms() const
{ return films; }

priority_queue<Cinema> CinemaFinder::getCinemas() const
{ return cinemas; }


// TODO


//b1
list<string> CinemaFinder::filmsWithActor(string actorName) const {
	list<string> res;

	// TODO
    for(auto iter=films.begin();iter!=films.end();iter++)
    {
        list<string> actors = iter->film->getActors();
        for(auto i=actors.begin();i!= actors.end();i++)
            if(*i==actorName) {
                res.push_back(iter->film->getTitle());
                break;
            }
    }
	return res;
}


//b2
void CinemaFinder::addActor(string filmTitle, string actorName) {

	// TODO
    for(auto iter=films.begin();iter!=films.end();iter++)
    {
        if(iter->film->getTitle()==filmTitle)
        {
            //(*iter).film->addActor(actorName);
            return;
        }
    }
    list<string> addN={actorName};
    Film add(filmTitle,addN);
    this->addFilm(&add);
}


//c1
string CinemaFinder::nearestCinema(string service1) const {
	string cName="";
	int maxDist=0;
	priority_queue<Cinema> aux, copy=cinemas;


	// TODO
    if(cinemas.size()!=0)
    {
        cName="";
        maxDist=0;
        aux.push(cinemas.top());
        copy.pop();
        while(!copy.empty())
        {
            if(cName=="")
            {
                list<string> serv=copy.top().getServices();
                for(auto it=serv.begin();it!=serv.end();it++)
                    if(*it==service1) {
                        maxDist = copy.top().getDistance();
                        cName = copy.top().getName();
                    }
            }
            else if(copy.top().getDistance()<maxDist)
            {
                list<string> serv=copy.top().getServices();
                for(auto it=serv.begin();it!=serv.end();it++)
                    if(*it==service1) {
                        maxDist = copy.top().getDistance();
                        cName = copy.top().getName();
                    }
            }
            copy.pop();
        }
    }
	return cName;
}


//c2
void CinemaFinder::addServiceToNearestCinema(string service1, unsigned maxDistance) {

	// TODO
	if(cinemas.empty())
	    throw CinemaNotFound();
	priority_queue<Cinema> copy;
    if(cinemas.top().getDistance()<maxDistance)
    {
        Cinema aux=cinemas.top();
        cinemas.pop();
        aux.addService(service1);
        cinemas.push(aux);
        return;
    }
    throw CinemaNotFound();
}
