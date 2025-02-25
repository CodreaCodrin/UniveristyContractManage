#pragma once

#include <assert.h>
#include <exception>

#include "../Domain/entity.h"
#include "../Domain/validator.h"
#include "../Repository/dataBase.h"
#include "../Service/service.h"
#include "../MyContainers/MyVector.h"

#define EXEPTION_WAS_THROWN(functie) \
	try \
	{ \
		functie; \
		assert(false);\
	} \
	catch (MyException&) \
	{ \
		assert(true); \
	} \

#define EXEPTION_WAS_NOT_THROWN(functie) \
	try \
	{ \
		functie; \
		assert(true);\
	} \
	catch (MyException&) \
	{ \
		assert(false); \
	} \


class Teste {
public:
	void test_all();
private:
	void test_entity();
	void test_validator_of_entity();
	void test_mylist();
	void test_Adauga();
	void test_Sterge();
	void test_Modifica();
	void test_undo();
	void test_filtare_ore();
	void test_filtare_prof();
	void test_sortare();
	void test_add_contract();
	//void test_vector();
	void test_contract();
	void test_dictionar();
	void test_repo_dictionar();
};