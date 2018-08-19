#include "Status.h"
bool Status::is_person_loaded = false;
bool Status::is_argument_input = false;
bool Status::is_form_filling_successful = false;
bool Status::get_is_person_loaded()
{
	return Status::is_person_loaded;
}

void Status::set_is_person_loaded(bool is_person_loaded)
{
	Status::is_person_loaded = is_person_loaded;
}

bool Status::get_is_argument_input()
{
	return Status::is_argument_input;
}

void Status::set_is_argument_input(bool is_argument_input)
{
	Status::is_argument_input = is_argument_input;
}

bool Status::get_is_form_filling_successful()
{
	return Status::is_form_filling_successful;
}

void Status::set_is_form_filling_successful(bool is_form_filling_successful)
{
	Status::is_form_filling_successful = is_form_filling_successful;
}
