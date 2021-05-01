/*
 * Cinema.cpp
 */
#include "Cinema.h"

Cinema::Cinema(string nm, unsigned d, unsigned nr): name(nm), distance(d),
		numberOfRooms(nr),timetable(FilmTime(0,NULL, 0))
{}

Cinema::Cinema(string nm, unsigned d, unsigned nr, list<string> ls): name(nm), distance(d),
		numberOfRooms(nr),services(ls), timetable(FilmTime(0,NULL,0))
{}

Cinema::~Cinema() { }

string Cinema::getName() const
{ return name; }

unsigned Cinema::getDistance() const
{ return distance; }

list<string> Cinema::getServices() const
{ return services; }

BST<FilmTime> Cinema::getTimetable() const
{ return timetable; }

void Cinema::addService(string service1)
{ services.push_back(service1); }

void Cinema::addFilmTime(const FilmTime &ft1)
{ timetable.insert(ft1); }


// TODO

bool Cinema::operator<(const Cinema & cr) const
{
	//TODO: Implement a correct version of the operator
	if(this->distance==cr.distance)
	    return this->getServices().size()>cr.getServices().size();
	return this->distance>cr.distance;
}


//a1
Film *Cinema::filmAtHour(unsigned &h1) const {
	Film *res = NULL;
	unsigned copy=h1;
	// TODO
    BSTItrIn<FilmTime> iterBfr(timetable);

    for(BSTItrIn<FilmTime> iter(timetable);!iter.isAtEnd();)
    {

        if(iter.retrieve().getHour()>h1)
        {
            h1=copy;
            return res;
        }
	    else if(iter.retrieve().getHour()==h1){
            res=iter.retrieve().getFilm();
            return res;
        }
	    else {
            res = iter.retrieve().getFilm();
            copy=iter.retrieve().getHour();
        }
	    iterBfr = iter;
	    iter.advance();
	    if(iter.isAtEnd())
        {
	        h1=iterBfr.retrieve().getHour();
            res=iterBfr.retrieve().getFilm();
            return res;
        }
    }
    return res;

}


//a2
bool Cinema::modifyHour(unsigned h1, unsigned room1, unsigned h2) {
	// TODO
    BSTItrPre<FilmTime> iter(timetable);
    BSTItrPre<FilmTime> iter2(timetable);
    while(!iter2.isAtEnd())
    {
        if(iter2.retrieve().getHour()==h2)
        {
            return false;
        }
        iter2.advance();
    }

    while(!iter.isAtEnd())
    {
        if(iter.retrieve().getHour()==h1 && iter.retrieve().getRoomID()==room1)
        {
            FilmTime add(h2,iter.retrieve().getFilm(),iter.retrieve().getRoomID());
            timetable.remove(iter.retrieve());
            timetable.insert(add);
            return true;
        }
        iter.advance();
    }
	return false;
}


//a3
unsigned Cinema::addFilm(Film *f1, unsigned h1) {
	unsigned roomToUse = 1;
	bool nextId=false, canUse=true;
	// TODO
	if(timetable.isEmpty())
    {
        FilmTime add(h1, f1, roomToUse);
        timetable.insert(add);
        return roomToUse;
    }
    for(BSTItrPre<FilmTime> iter(timetable);!iter.isAtEnd();)
    {

        if(iter.retrieve().getRoomID()==roomToUse)
            if(iter.retrieve().getHour()==h1)
                canUse=false;

        iter.advance();

        if(iter.isAtEnd()) {
            if (canUse) {
                FilmTime add(h1, f1, roomToUse);
                timetable.insert(add);
                return roomToUse;
            }
            if (roomToUse!=this->numberOfRooms) {
                nextId = false;
                roomToUse++;
                canUse = true;
                BSTItrPre<FilmTime> iter2(timetable);
                iter = iter2;
            }
        }
    }

	return 0;
}






