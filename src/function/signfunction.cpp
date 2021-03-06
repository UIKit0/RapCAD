#include "signfunction.h"
#include "numbervalue.h"

SignFunction::SignFunction() : Function("sign")
{
	addParameter("value");
}

decimal SignFunction::sign(decimal num)
{
	return num<0?-1.0:num>0?1.0:0.0;
}

Value* SignFunction::evaluate(Context* ctx)
{
	NumberValue* numVal=dynamic_cast<NumberValue*>(getParameterArgument(ctx,0));
	if(numVal) {
		decimal num=numVal->getNumber();

		return new NumberValue(sign(num));
	}
	return new Value();
}
