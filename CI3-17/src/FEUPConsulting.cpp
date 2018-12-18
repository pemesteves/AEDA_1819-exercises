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
	Expertize exp = getExpertize(expertizeAvailable, cost);
	if((exp.getName() != expertizeAvailable) || (exp.getCost() != cost)){

		Expertize novo = Expertize(expertizeAvailable, cost);
		novo.addConsultant(student);
		expertizes.insert(novo);
		return;
	}

	expertizes.remove(exp);
	exp.addConsultant(student);
	expertizes.insert(exp);



}

vector<Student*> FEUPConsulting::getCandidateStudents(Project* project) const {
	vector<Student*> temp;
	vector<Student*> consult;
	BSTItrIn<Expertize> it(expertizes);
	while(!it.isAtEnd()){
		if(it.retrieve().getName() == project->getExpertize() && it.retrieve().getCost() == project->getCost()){
			consult = it.retrieve().getConsultants();
			for(vector<Student*>::iterator it1 = consult.begin(); it1 != consult.end(); it1++){
				if((*it1)->getCurrentProject() == ""){
					temp.push_back(*it1);
				}
			}
		}
		it.advance();
	}
	return temp;

}


bool FEUPConsulting::assignProjectToStudent(Project* project, Student* student) {
	if(project->getConsultant() != NULL)
		return false;
	if(student->getCurrentProject() != "")
		return false;

	vector<Student*> tmp = getCandidateStudents(project);
	vector<Student*>::iterator it = tmp.begin();
	for(; it != tmp.end(); it++){
		if((*it)->getName() == student->getName() && (*it)->getEMail() == student->getEMail()){
			project->setConsultant(*it);
			student->addProject(project->getTitle());
			return true;
		}
	}
	return false;

}

//
// TODO: Part II  - Hash Table
//

void FEUPConsulting::addStudent(Student* student) {
	StudentPtr s(student);
	students.insert(s);
}

void FEUPConsulting::changeStudentEMail(Student* student, string newEMail) {
	StudentPtr s(student);
	HashTabStudentPtr::iterator it = students.find(s);
	if (it != students.end()){
		students.erase(it);
		s.setEMail(newEMail);
		students.insert(s);
	}
}


//
// TODO: Part III - Priority Queue
//

void FEUPConsulting::addActiveStudents(const vector<Student>& candidates, int min) {
	vector<Student>::const_iterator it = candidates.begin();
	for(; it != candidates.end(); it++){
		if ((*it).getPastProjects().size() >= min){
			activeStudents.push(*it);
		}
	}
}


int FEUPConsulting::mostActiveStudent(Student& studentMaximus) {
	Student s("", ""), s1("", "");
	int numProj = 0;
	priority_queue<Student> activeS = activeStudents;

	while(!activeS.empty()){
		s1 = activeS.top();
		activeS.pop();
		if(s1.getPastProjects().size() > numProj){
			numProj = s1.getPastProjects().size();
			s = s1;
		}
		else if (s1.getPastProjects().size() == numProj && numProj != 0){
			return 0;
		}
	}
	studentMaximus = s;
	return activeStudents.size();

}





















