#include <iostream>
#include <fstream>
#include <string>

#include "table.h"
#include "intermediate.h"

using namespace std;

void
_test_table()
{
	cout << "Test Table" << endl << endl;

	Table *a = new Table;
	Table *b = new Table;

	cout << "b->addAttribute(\"A\")           Should be true:  " << boolalpha << b->addAttribute("A") << endl;
	cout << "b->addAttribute(\"B\", 2)        Should be false: " << boolalpha << b->addAttribute("B", 2) << endl;
	cout << "b->addAttribute(\"B\", -2)       Should be false: " << boolalpha << b->addAttribute("B", -2) << endl;

	cout << endl;

	string entry1[] = {"A1"};
	cout << "b->addEntry(entry1)            Should be true:  " << boolalpha << b->addEntry(entry1) << endl;
	cout << "b->addEntry(entry1, 2)         Should be false: " << boolalpha << b->addEntry(entry1, 2) << endl;
	cout << "b->addEntry(entry1, -2)        Should be false: " << boolalpha << b->addEntry(entry1, -2) << endl;

	cout << endl;

	cout << "b->addAttribute(\"C\", 1, \"C1\")  Should be true:  " << boolalpha << b->addAttribute("C", 1, "C1") << endl;
	cout << "b->addAttribute(\"B\", 1, \"B1\")  Should be true:  " << boolalpha << b->addAttribute("B", 1, "B1") << endl;

	cout << endl;

	string entry2[] = {"A2", "B2", "C2"};
	string entry3[] = {"A3", "B3", "C3"};
	string entry4[] = {"A4", "B4", "C4"};

	cout << "b->addEntry(entry4)            Should be true:  " << boolalpha << b->addEntry(entry4) << endl;
	cout << "b->addEntry(entry2, 1)         Should be true:  " << boolalpha << b->addEntry(entry2, 1) << endl;
	cout << "b->addEntry(entry3, 2)         Should be true:  " << boolalpha << b->addEntry(entry3, 2) << endl;

	cout << endl;

	cout << "b->deleteEntry(-1)             Should be false: " << boolalpha << b->deleteEntry(-1) << endl;
	cout << "b->deleteEntry(4)              Should be false: " << boolalpha << b->deleteEntry(4) << endl;
	cout << "b->deleteEntry(3)              Should be true:  " << boolalpha << b->deleteEntry(3) << endl;
	cout << "b->deleteEntry(0)              Should be true:  " << boolalpha << b->deleteEntry(0) << endl;

	cout << endl;

	cout << "b->deleteAttribute(3)          Should be false: " << boolalpha << b->deleteAttribute(3) << endl;
	cout << "b->deleteAttribute(-1)         Should be false: " << boolalpha << b->deleteAttribute(-1) << endl;
	cout << "b->deleteAttribute(2)          Should be true:  " << boolalpha << b->deleteAttribute(2) << endl;

	cout << endl;

	Table *c = new Table {*b};
	Table *d = new Table {*b};

	cout << "b->append(c)                   Should be true:  " << boolalpha << b->append(*c) << endl;

	cout << endl;

	cout << "d->deleteAttribute(1)          Should be true:  " << boolalpha << d->deleteAttribute(1) << endl;
	cout << "d->append(b)                   Should be false: " << boolalpha << d->append(*b) << endl;

	cout << endl;

	cout << "d->addAttribute(\"C\")           Should be true:  " << boolalpha << d->addAttribute("C") << endl;
	cout << "d->append(b)                   Should be false: " << boolalpha << d->append(*b) << endl;

	cout << endl;

	cout << "Remove all entries from d" << endl;
	cout << "d->deleteEntry(1)              Should be true:  " << boolalpha << d->deleteEntry(1) << endl;
	cout << "d->deleteEntry(0)              Should be true:  " << boolalpha << d->deleteEntry(0) << endl;

	cout << endl;

	cout << "Remove all attributes from c" << endl;
	cout << "c->deleteAttribute(1)          Should be true:  " << boolalpha << c->deleteAttribute(1) << endl;
	cout << "c->deleteAttribute(0)          Should be true:  " << boolalpha << c->deleteAttribute(0) << endl;

	// Note: a, b, c and d are deleted here
	delete a;
	delete b;
	delete c;
	delete d;

	cout << endl;
}

void
_test_intermediate()
{
	cout << "Test Intermediate" << endl << endl;

	Table courses;

	courses.addAttribute("Department");
	courses.addAttribute("Course Code");
	courses.addAttribute("Course Name");
	courses.addAttribute("Credits");

	Table cse {courses};
	Table math {courses};

	string comp1001[] {"CSE", "COMP1001", "Exploring Multimedia and Internet Computing", "3"};
	string comp1021[] {"CSE", "COMP1021", "Introduction to Computer Science", "3"};
	string comp1022p[] {"CSE", "COMP1022P", "Introduction to Computing with Java", "3"};
	string comp1022q[] {"CSE", "COMP1022Q", "Introduction to Computing with Excel VBA", "3"};
	string comp1029c[] {"CSE", "COMP1029C", "C Programming Bridging Course", "1"};
	string comp1029j[] {"CSE", "COMP1029J", "Java Programming Bridging Course", "1"};
	string comp1029p[] {"CSE", "COMP1029P", "Python Programming Bridging Course", "1"};
	string comp1029v[] {"CSE", "COMP1029V", "Excel VBA Programming Bridging Course", "1"};
	string comp1942[] {"CSE", "COMP1942", "Exploring and Visualizing Data", "3"};
	string comp2011[] {"CSE", "COMP2011", "Programming with C++", "4"};
	string comp2012[] {"CSE", "COMP2012", "Object-Oriented Programming and Data Structures", "4"};
	string comp2611[] {"CSE", "COMP2611", "Computer Organization", "4"};
	string comp2711[] {"CSE", "COMP2711", "Discrete Mathematical Tools for Computer Science", "4"};
	string comp3021[] {"CSE", "COMP3021", "Java Programming", "3"};
	string comp3071[] {"CSE", "COMP3071", "Honors Competitive Programming", "2"};
	string comp3111[] {"CSE", "COMP3111", "Software Engineering", "4"};
	string comp3311[] {"CSE", "COMP3311", "Database Management Systems", "3"};
	string comp3511[] {"CSE", "COMP3511", "Operating Systems", "3"};
	string comp3632[] {"CSE", "COMP3632", "Principles of Cybersecurity", "3"};
	string comp3711[] {"CSE", "COMP3711", "Design and Analysis of Algorithms", "3"};
	string comp4021[] {"CSE", "COMP4021", "Internet Computing", "3"};
	string comp4111[] {"CSE", "COMP4111", "Software Engineering Practices", "3"};
	string comp4211[] {"CSE", "COMP4211", "Machine Learning", "3"};
	string comp4221[] {"CSE", "COMP4221", "Introduction to Natural Language Processing", "3"};
	string comp4321[] {"CSE", "COMP4321", "Search Engines for Web and Enterprise Data", "3"};
	string comp4331[] {"CSE", "COMP4331", "Data Mining", "3"};
	string comp4332[] {"CSE", "COMP4332", "Big Data Mining and Management", "3"};
	string comp4411[] {"CSE", "COMP4411", "Computer Graphics", "3"};
	string comp4431[] {"CSE", "COMP4431", "Multimedia Computing", "3"};
	string comp4441[] {"CSE", "COMP4441", "Computer Music", "3"};
	string comp4462[] {"CSE", "COMP4462", "Data Visualization", "3"};
	string comp4471[] {"CSE", "COMP4471", "Deep Learning in Computer Vision", "3"};
	string comp4511[] {"CSE", "COMP4511", "System and Kernel Programming in Linux", "3"};
	string comp4521[] {"CSE", "COMP4521", "Mobile Application Development", "3"};
	string comp4611[] {"CSE", "COMP4611", "Design and Analysis of Computer Architecture", "3"};
	string comp4621[] {"CSE", "COMP4621", "Computer Communication Networks I", "3"};
	string comp4631[] {"CSE", "COMP4631", "Computer and Communication Security", "3"};
	string comp4632[] {"CSE", "COMP4632", "Practicing Cybersecurity: Attacks and Counter-measures", "3"};
	string comp4641[] {"CSE", "COMP4641", "Social Information Network Analysis and Engineering", "3"};

	string math1012[] {"MATH", "MATH1012", "Calculus IA", "4"};
	string math1013[] {"MATH", "MATH1013", "Calculus IB", "3"};
	string math1014[] {"MATH", "MATH1014", "Calculus II", "3"};
	string math1024[] {"MATH", "MATH1024", "Honors Calculus II", "3"};
	string math2011[] {"MATH", "MATH2011", "Introduction to Multivariable Calculus", "3"};
	string math2023[] {"MATH", "MATH2023", "Multivariable Calculus", "4"};
	string math2033[] {"MATH", "MATH2033", "Mathematical Analysis", "4"};
	string math2043[] {"MATH", "MATH2043", "Honors Mathematical Analysis", "4"};
	string math2111[] {"MATH", "MATH2111", "Matrix Algebra and Applications", "3"};
	string math2121[] {"MATH", "MATH2121", "Linear Algebra", "4"};
	string math2343[] {"MATH", "MATH2343", "Discrete Structures", "4"};
	string math2350[] {"MATH", "MATH2350", "Applied Linear Algebra and Differential Equations", "3"};
	string math2351[] {"MATH", "MATH2351", "Introduction to Differential Equations", "3"};
	string math2352[] {"MATH", "MATH2352", "Differential Equations", "4"};
	string math2411[] {"MATH", "MATH2411", "Applied Statistics", "4"};
	string math2421[] {"MATH", "MATH2421", "Probability", "4"};
	string math2431[] {"MATH", "MATH2431", "Honors Probability", "4"};
	string math2741[] {"MATH", "MATH2741", "Geometric Constructions", "3"};
	string math3033[] {"MATH", "MATH3033", "Real Analysis", "4"};
	string math3131[] {"MATH", "MATH3131", "Honors in Linear and Abstract Algebra II", "4"};
	string math3322[] {"MATH", "MATH3322", "Matrix Computation", "3"};
	string math3343[] {"MATH", "MATH3343", "Combinatorial Analysis", "3"};
	string math3423[] {"MATH", "MATH3423", "Statistical Inference", "3"};
	string math3424[] {"MATH", "MATH3424", "Regression Analysis", "3"};
	string math3425[] {"MATH", "MATH3425", "Stochastic Modeling", "3"};
	string math3426[] {"MATH", "MATH3426", "Sampling", "3"};
	string math4023[] {"MATH", "MATH4023", "Complex Analysis", "3"};
	string math4033[] {"MATH", "MATH4033", "Calculus on Manifolds", "3"};
	string math4051[] {"MATH", "MATH4051", "Theory of Ordinary Differential Equations", "3"};
	string math4052[] {"MATH", "MATH4052", "Partial Differential Equations", "3"};
	string math4221[] {"MATH", "MATH4221", "Euclidean and Non-Euclidean Geometries", "3"};
	string math4225[] {"MATH", "MATH4225", "Topology", "3"};
	string math4321[] {"MATH", "MATH4321", "Game Theory", "3"};
	string math4425[] {"MATH", "MATH4425", "Introductory Time Series", "3"};
	string math4428[] {"MATH", "MATH4428", "Bayesian Analysis and Credibility Theory", "3"};
	string math4512[] {"MATH", "MATH4512", "Fundamentals of Mathematical Finance", "3"};
	string math4513[] {"MATH", "MATH4513", "Life Contingencies Models and Insurance Risk", "3"};
	string math4514[] {"MATH", "MATH4514", "Financial Economics in Actuarial Science", "3"};

	cse.addEntry(comp1001);
	cse.addEntry(comp1021);
	cse.addEntry(comp1022p);
	cse.addEntry(comp1022q);
	cse.addEntry(comp1029c);
	cse.addEntry(comp1029j);
	cse.addEntry(comp1029p);
	cse.addEntry(comp1029v);
	cse.addEntry(comp1942);
	cse.addEntry(comp2011);
	cse.addEntry(comp2012);
	cse.addEntry(comp2611);
	cse.addEntry(comp2711);
	cse.addEntry(comp3021);
	cse.addEntry(comp3071);
	cse.addEntry(comp3111);
	cse.addEntry(comp3311);
	cse.addEntry(comp3511);
	cse.addEntry(comp3632);
	cse.addEntry(comp3711);
	cse.addEntry(comp4021);
	cse.addEntry(comp4111);
	cse.addEntry(comp4211);
	cse.addEntry(comp4221);
	cse.addEntry(comp4321);
	cse.addEntry(comp4331);
	cse.addEntry(comp4332);
	cse.addEntry(comp4411);
	cse.addEntry(comp4431);
	cse.addEntry(comp4441);
	cse.addEntry(comp4462);
	cse.addEntry(comp4471);
	cse.addEntry(comp4511);
	cse.addEntry(comp4521);
	cse.addEntry(comp4611);
	cse.addEntry(comp4621);
	cse.addEntry(comp4631);
	cse.addEntry(comp4632);
	cse.addEntry(comp4641);

	math.addEntry(math1012);
	math.addEntry(math1013);
	math.addEntry(math1014);
	math.addEntry(math1024);
	math.addEntry(math2011);
	math.addEntry(math2023);
	math.addEntry(math2033);
	math.addEntry(math2043);
	math.addEntry(math2111);
	math.addEntry(math2121);
	math.addEntry(math2343);
	math.addEntry(math2350);
	math.addEntry(math2351);
	math.addEntry(math2352);
	math.addEntry(math2411);
	math.addEntry(math2421);
	math.addEntry(math2431);
	math.addEntry(math2741);
	math.addEntry(math3033);
	math.addEntry(math3131);
	math.addEntry(math3322);
	math.addEntry(math3343);
	math.addEntry(math3423);
	math.addEntry(math3424);
	math.addEntry(math3425);
	math.addEntry(math3426);
	math.addEntry(math4023);
	math.addEntry(math4033);
	math.addEntry(math4051);
	math.addEntry(math4052);
	math.addEntry(math4221);
	math.addEntry(math4225);
	math.addEntry(math4321);
	math.addEntry(math4425);
	math.addEntry(math4428);
	math.addEntry(math4512);
	math.addEntry(math4513);
	math.addEntry(math4514);

	courses.append(cse);
	courses.append(math);

	cout << "Query 1. Prints all courses" << endl;
	courses.query().select();

	cout << endl;

	cout << "Query 2. Prints the Course Name and Course Code of the first 5 rows" << endl;

	string selector[] = {"Course Name", "Course Code"};
	courses.query().limit(5).select(selector, 2);

	cout << endl;

	cout << "Query 3. rints the Department, Course Name and Credits of the courses that have \"Analysis\" in their Course Name " << endl;
	cout << "ordered by increasing Credits then decreasing Department" << endl;
	
	string selector2[] = {"Department", "Course Name", "Credits"};
	courses.query().where("Course Name", CONTAINS, "Analysis").orderBy("Department", DESCENDING).orderBy("Credits", ASCENDING).select(selector2, 3);

	cout << endl;

	cout << "Query 4. Updates the Credit of the courses that have \"Programming\" in their Course Name to 5" << endl;
	
	courses.query().where("Course Name", CONTAINS, "Programming").update("Credits", "5");

	cout << endl;

	cout << "Query 5. Prints the courses with 5 credits" << endl;
	
	courses.query().where("Credits", EQ, "5").select();

	cout << endl;
}

int
main()
{
	_test_table();

	_test_intermediate();

	return 0;
}
