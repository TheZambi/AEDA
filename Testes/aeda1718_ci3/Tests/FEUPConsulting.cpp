/*
 * FEUPConsulting.cpp
 *
 *  Created on: 10/12/2017
 *      Author: CS
 */

#include "FEUPConsulting.h"

FEUPConsulting::FEUPConsulting(): expertizes(Expertize("", 0)) {
}

FEUPConsulting::FEUPConsulting(vector<Project*> projects): expertizes(Expertize("", 0)) {
	this->projects = projects;
}

void FEUPConsulting::addProjects(vector<Project*> projects) {
	this->projects = projects;
}

vector<Project*> FEUPConsulting::getProjects() const{
	return this->projects;
}


// get the expertize objet with the given name, including all students with the corresponding skills
Expertize FEUPConsulting::getExpertize(string name, unsigned cost) {
	Expertize itemNotFound("", 0);
	Expertize expertize(name, cost);
	Expertize search = expertizes.find(expertize);

	return search;
}


void FEUPConsulting::addProject(Project* project) {
	//TODO
	Expertize itemNotFound("", 0);
	Expertize expertize(project->getExpertize(), project->getCost());
	Expertize search = expertizes.find(expertize);

	if(search == itemNotFound) {
		this->expertizes.insert(expertize);
	}

	projects.push_back(project);
}

BST<Expertize> FEUPConsulting::getExpertizes() const {
	return this->expertizes;
}

void FEUPConsulting::addNewExpertize(const Expertize & expertize1) {
	this->expertizes.insert(expertize1);
}

vector<StudentPtr> FEUPConsulting::getStudents() const {
	vector<StudentPtr> ptrs;
	HashTabStudentPtr::const_iterator it1 = this->students.begin();
	HashTabStudentPtr::const_iterator it2 = this->students.end();
	for(; it1 != it2; it1++) {
			ptrs.push_back(*it1); //We can make it a bit more complex by considering only records with a condition!
	}
	return ptrs;
}

void FEUPConsulting::setStudents(vector<StudentPtr>& newStudents) {
	for(int i = 0; i < newStudents.size(); i++) students.insert(newStudents[i]);
}

priority_queue<Student> FEUPConsulting::getActiveStudents() const {
	return activeStudents;
}
void FEUPConsulting::setActiveStudents(priority_queue<Student>& students) {
	activeStudents = students;
}


//
// TODO: Part I   - BST
//

void FEUPConsulting::addAvailability(Student* student, string expertizeAvailable, unsigned cost) {
	//TODO
	BSTItrPre<Expertize> iter(expertizes);
    for(;!iter.isAtEnd();iter.advance())
    {
        if(iter.retrieve().getCost()==cost && iter.retrieve().getName()==expertizeAvailable) {
            iter.retrieve().addConsultant(student);
            return;
        }

    }
    Expertize add(expertizeAvailable, cost);
    add.addConsultant(student);
    this->addNewExpertize(add);
}

vector<Student*> FEUPConsulting::getCandidateStudents(Project* project) const {
	vector<Student*> temp;
	//TODO:
	BSTItrPre<Expertize> iter(expertizes);
	for(;!iter.isAtEnd();iter.advance())
    {
	    if(iter.retrieve().getName()==project->getExpertize() && iter.retrieve().getCost()==project->getCost())
        {
	        for(size_t i=0;i<iter.retrieve().getConsultants().size();i++)
	            if(iter.retrieve().getConsultants().at(i)->getCurrentProject()=="")
	                temp.push_back(iter.retrieve().getConsultants().at(i));
	        return temp;
        }
    }
	return temp;

}


bool FEUPConsulting::assignProjectToStudent(Project* project, Student* student) {
	//TODO:
	vector<Student*> stud=getCandidateStudents(project);
	if(project->getConsultant()==NULL)
        for(size_t i=0;i<stud.size();i++) {
            if (stud.at(i)->getName() == student->getName() && stud.at(i)->getEMail() == student->getEMail()) {
                student->addProject(project->getTitle());
                project->setConsultant(student);
                return true;
            }
        }
	return false;

}

//
// TODO: Part II  - Hash Table
//

void FEUPConsulting::addStudent(Student* student) {
	//TODO:
    this->students.insert(student);
}

void FEUPConsulting::changeStudentEMail(Student* student, string newEMail) {
	//TODO
    if(students.find(student)!=students.end())
    {
        students.erase(student);
        student->setEMail(newEMail);
        this->addStudent(student);
        return;
    }
}


//
// TODO: Part III - Priority Queue
//

void FEUPConsulting::addActiveStudents(const vector<Student>& candidates, int min) {
	//TODO:
    for(size_t i=0; i<candidates.size();i++)
    {
        if(candidates.at(i).getPastProjects().size()>=min)
            this->activeStudents.push(candidates.at(i));
    }
}


int FEUPConsulting::mostActiveStudent(Student& studentMaximus) {
	//TODO:

	if(activeStudents.size()==0)
	    return 0;

	bool counter = 0;

	Student aux("","");
	aux = activeStudents.top();


    priority_queue<Student> auxQ;


    auxQ.push(activeStudents.top());

    activeStudents.pop();

    while(!activeStudents.empty())
    {
        if(aux.getPastProjects().size()==activeStudents.top().getPastProjects().size())
            counter=true;
        else if (aux.getPastProjects().size()<activeStudents.top().getPastProjects().size())
        {
            aux=activeStudents.top();
            counter=false;
        }
        auxQ.push(activeStudents.top());
        activeStudents.pop();
    }

    activeStudents=auxQ;

    if(counter) {
        return 0;
    }

    studentMaximus=aux;


    return activeStudents.size();

}





















