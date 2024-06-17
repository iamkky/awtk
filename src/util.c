#include <abd/new.h>
#include <abd/errLog.h>
#include <abd/AString.c.h>
#include <abjson/json.h>

AData awtkParsesJson(AString json)
{
JsonParser	parser;
AData		value;
int		lcount, result;

	if(nullAssert(json)) return NULL;
	if(nullAssert(json->buffer)) return NULL;

	parser = JsonParserNew(aStringGetBuffer(json), &lcount);

	lcount = 0;
	result = JsonParserParse(parser);

	if(result>0){
		value = parser->value[0].value;	// output result is in the value of the first positon of values stack
	}else{
		value = NULL;
		errLogf("Error parsing json, line %d\n", lcount);
	}

	JsonParserFree(parser);

	return value;
}

