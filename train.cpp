#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Bad_Input_Execptoin
{
public:
	Bad_Input_Execptoin(int n, string input_type)
	{
		experision = "unassignable";
		experision.append(input_type);
		experision.append(" at ");
		experision.append(to_string(n+1));
		experision.append("th place.");
	}
	string experision;
};

// Can I use template elements forming class name?
class Bad_Code_Exception : public Bad_Input_Execptoin
{
public:
	Bad_Code_Exception(int n)
	:Bad_Input_Execptoin(n, "National code Number")
	{
	}
};

class Bad_Phone_Exception : public Bad_Input_Execptoin
{
public:
	Bad_Phone_Exception(int n)
	:Bad_Input_Execptoin(n, "Phone Number")
	{
	}
};

// TODO: Read and document about lambda functions.
template<typename T, int n, T d, T u, class ex>
void array_copy(T a1[n], T a2[n]) {
    for (int i = 0; i < n; ++i)
			if ((a1[i] < u + 1) && (a1[i] > d - 1))
				a2[i] = a1[i];
			else
				throw ex(i);
}

struct N_Code_1
{
	N_Code_1(char p1[3], char p2[6], char p3[1])
	{
		// TODO: ask is there any better way?
		// part2[5] = p2[5];
		array_copy<char, 3, '0', '9', Bad_Code_Exception> (p1, part1);
		array_copy<char, 6, '0', '9', Bad_Code_Exception> (p2, part2);
		array_copy<char, 1, '0', '9', Bad_Code_Exception> (p3, part3);
	}
	char part1[3];
	char part2[6];
	char part3[1];
};

struct N_Code_2 // where to write exeption
{
	N_Code_2(char c[10])
	{
		// TODO: ask is there any better way?
		array_copy<char, 10, '0', '9', Bad_Code_Exception> (c, code);
	}
	char code[10];
};

struct Phone_Number
{
	Phone_Number(char p[3], char n[8])
	{
		array_copy<char, 3, '0', '9', Bad_Phone_Exception> (p, pre);
		array_copy<char, 8, '0', '9', Bad_Phone_Exception> (n, number);
	}
	char pre[3];
	char number[8];
};

// TODO: implement date.
class Date
{
public:
	Date(int y)
	:year(y)
	{
	}
private:
	int year;
};

class Kanoon;

class School
{
public:
	School(string n, Phone_Number p_n)
	:name(n)
	,phone(p_n)
	{
	}
private:
	string name;
	Phone_Number phone;
};

class Member
{
public:
	Member(N_Code_2 N_C, int g, Phone_Number h_n, Date d, Kanoon *k);
private:
	N_Code_2 N_code;
	int group;
	Phone_Number home;
	Date enrolment;
	Kanoon *kanoon;
};

// TODO: N_C throw must be catched before.
Member::Member(N_Code_2 N_C, int g, Phone_Number h_n, Date d, Kanoon *k)
:N_code(N_C)
,group(g)
,home(h_n)
,enrolment(d)
,kanoon(k)
{
}

class Collegian : public Member
{
public:
	Collegian(N_Code_2 N_C, int g, Phone_Number h_n, Date d, Kanoon *k);
};

class Event;

class Responsible : public Member
{
public:
	Responsible(N_Code_2 N_C, int g, Phone_Number h_n, Date d, Kanoon *k, Event *e);
	Responsible(N_Code_2 N_C, int g, Phone_Number h_n, Date d, Kanoon *k, vector<Event*> ve);
	void add_resp(Event *e);
private:
	vector<Event*> events;
};

// TODO: add more methods to Event.
class Event
{
public:
	Event(vector<Responsible*> r, vector<Member*> e)
	:responsibles(r)
	,enrollees(e)
	{
		for (auto it = r.begin(); it != r.end(); ++it)
		{
			enroll(*it);
		}
	}
	Event(Member *m)
	{
		enroll(m);
	}
private:
	vector<Responsible*> responsibles;
	vector<Member*> enrollees;
	void enroll(Member *m) { enrollees.push_back(m); }
	friend class Kanoon;
	friend class Responsible;
};

Responsible::Responsible(N_Code_2 N_C, int g, Phone_Number h_n, Date d, Kanoon *k, Event *e)
	:Member(N_C, g, h_n, d, k)
	{
		events.push_back(e);
		e->enroll(this);
	}

Responsible::Responsible(N_Code_2 N_C, int g, Phone_Number h_n, Date d, Kanoon *k, vector<Event*> ve)
	:Member(N_C, g, h_n, d, k)
	,events(ve)
	{
		for (auto it = ve.begin(); it != ve.end(); ++it)
		{
			(*it)->enroll(this);
		}
	}

void Responsible::add_resp(Event *e)
	{
		events.push_back(e);
		e->enroll(this);
	}

class Student : public Member
{
public:
	Student();
private:
	School *school;
	vector<Event*> events;
};

class Group;

class Mentor : public Collegian, public Responsible
{
public:
	Mentor(N_Code_2 N_C, int g, Phone_Number h_n, Date d, Kanoon *k, Group *gr);
private:
	vector<Group*> groups;
};

// TODO: check if all member ahve same group number.
class Group : public Event
{
public:
	Group(Mentor *mentor, vector<Member*> e)
	:Event(vector<Responsible*> {mentor}, e)
	{
	}
};

Mentor::Mentor(N_Code_2 N_C, int g, Phone_Number h_n, Date d, Kanoon *k, Group *gr)
:Collegian(N_C, g, h_n, d, k)
,Responsible(N_C, g, h_n, d, k, gr)
{
}

class Kanoon
{
public:
	Kanoon(string n):name(n) {}
private:
	string name;
	Event *public_council;
	friend class Member;
private:
	void add_pc_member(Member *m);
	friend class Collegian;
};

// TODO: check if member is coleagian.
void Kanoon::add_pc_member(Member *m)
{
	if (public_council == NULL)
		public_council = new Event(m);
	else
		public_council->enrollees.push_back(m);
}

Collegian::Collegian(N_Code_2 N_C, int g, Phone_Number h_n, Date d, Kanoon *k)
	:Member(N_C, g, h_n, d, k)
	{
		k->add_pc_member(this);
	}

int main(int argc, char const *argv[])
{
	Kanoon E_A("19");
	char c1[10] = {'0','9','2','1','7','7','7','5','0','7'};
	N_Code_2 NC(c1);
	char c2[3] = {'0','2','1'};
	char c3[8] = {'5','5','3','6','6','1','1','7'};
	Phone_Number PN(c2,c3);
	Collegian killer(NC, 12, PN, Date(1384), &E_A);
	E_A.ss();
	return 0;
}



