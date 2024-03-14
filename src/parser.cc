
#include "parser.h"

parser *new_parser(std::vector<token> *ptstream)
{
	parser *p = new parser;

	p->cur_idx = 0;
	p->ptoken_stream = ptstream;
	p->pcur_token = &(*ptstream)[0];
	p->pnext_token = &(*ptstream)[1];
	return p;
}

void delete_parser(parser *self)
{
	delete self;
}

void move_next_token(parser *self)
{
	if (self->cur_idx < self->ptoken_stream->size() - 1)
	{
		self->cur_idx++;
		self->pcur_token = &(*self->ptoken_stream)[self->cur_idx];
		self->pnext_token = &(*self->ptoken_stream)[self->cur_idx + 1];
	}
	else if (self->cur_idx == self->ptoken_stream->size() - 1)
	{
		self->cur_idx = self->ptoken_stream->size() - 1;
		self->pcur_token = &(*self->ptoken_stream)[self->cur_idx];
		self->pnext_token = NULL;
	}
	else
	{
		self->cur_idx = self->ptoken_stream->size();
		self->pcur_token = NULL;
		self->pnext_token = NULL;
	}
}
