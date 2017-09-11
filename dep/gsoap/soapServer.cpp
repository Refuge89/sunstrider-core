/* soapServer.cpp
   Generated by gSOAP 2.8.17r from gsoap.stub

Copyright(C) 2000-2013, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
GPL or Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#if defined(__BORLANDC__)
#pragma option push -w-8060
#pragma option push -w-8004
#endif
#include "soapH.h"

SOAP_SOURCE_STAMP("@(#) soapServer.cpp ver 2.8.17r 2014-06-21 21:43:17 GMT")


extern "C" SOAP_FMAC5 int SOAP_FMAC6 soap_serve(struct soap *soap)
{
#ifndef WITH_FASTCGI
    unsigned int k = soap->max_keep_alive;
#endif
    do
    {
#ifndef WITH_FASTCGI
        if (soap->max_keep_alive > 0 && !--k)
            soap->keep_alive = 0;
#endif
        if (soap_begin_serve(soap))
        {    if (soap->error >= SOAP_STOP)
                continue;
            return soap->error;
        }
        if (soap_serve_request(soap) || (soap->fserveloop && soap->fserveloop(soap)))
        {
#ifdef WITH_FASTCGI
            soap_send_fault(soap);
#else
            return soap_send_fault(soap);
#endif
        }

#ifdef WITH_FASTCGI
        soap_destroy(soap);
        soap_end(soap);
    } while (1);
#else
    } while (soap->keep_alive);
#endif
    return SOAP_OK;
}

#ifndef WITH_NOSERVEREQUEST
extern "C" SOAP_FMAC5 int SOAP_FMAC6 soap_serve_request(struct soap *soap)
{
    soap_peek_element(soap);
    if (!soap_match_tag(soap, soap->tag, "ns1:executeCommand"))
        return soap_serve_ns1__executeCommand(soap);
    return soap->error = SOAP_NO_METHOD;
}
#endif

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns1__executeCommand(struct soap *soap)
{    struct ns1__executeCommand soap_tmp_ns1__executeCommand;
    struct ns1__executeCommandResponse soap_tmp_ns1__executeCommandResponse;
    char * soap_tmp_string;
    soap_default_ns1__executeCommandResponse(soap, &soap_tmp_ns1__executeCommandResponse);
    soap_tmp_string = NULL;
    soap_tmp_ns1__executeCommandResponse.result = &soap_tmp_string;
    soap_default_ns1__executeCommand(soap, &soap_tmp_ns1__executeCommand);
    if (!soap_get_ns1__executeCommand(soap, &soap_tmp_ns1__executeCommand, "ns1:executeCommand", NULL))
        return soap->error;
    if (soap_body_end_in(soap)
     || soap_envelope_end_in(soap)
     || soap_end_recv(soap))
        return soap->error;
    soap->error = ns1__executeCommand(soap, soap_tmp_ns1__executeCommand.command, soap_tmp_ns1__executeCommandResponse.result);
    if (soap->error)
        return soap->error;
    soap->encodingStyle = NULL;
    soap_serializeheader(soap);
    soap_serialize_ns1__executeCommandResponse(soap, &soap_tmp_ns1__executeCommandResponse);
    if (soap_begin_count(soap))
        return soap->error;
    if (soap->mode & SOAP_IO_LENGTH)
    {    if (soap_envelope_begin_out(soap)
         || soap_putheader(soap)
         || soap_body_begin_out(soap)
         || soap_put_ns1__executeCommandResponse(soap, &soap_tmp_ns1__executeCommandResponse, "ns1:executeCommandResponse", NULL)
         || soap_body_end_out(soap)
         || soap_envelope_end_out(soap))
             return soap->error;
    };
    if (soap_end_count(soap)
     || soap_response(soap, SOAP_OK)
     || soap_envelope_begin_out(soap)
     || soap_putheader(soap)
     || soap_body_begin_out(soap)
     || soap_put_ns1__executeCommandResponse(soap, &soap_tmp_ns1__executeCommandResponse, "ns1:executeCommandResponse", NULL)
     || soap_body_end_out(soap)
     || soap_envelope_end_out(soap)
     || soap_end_send(soap))
        return soap->error;
    return soap_closesock(soap);
}

#if defined(__BORLANDC__)
#pragma option pop
#pragma option pop
#endif

/* End of soapServer.cpp */
