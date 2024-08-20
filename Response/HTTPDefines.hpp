#pragma once


//-----------------------------400-----------------------------
#define BAD_REQUEST_ERROR "HTTP/1.1 400 Bad Request\r\n" \
						  "Content-Type: text/html\r\n\r\n"

#define BAD_REQUEST_ERROR_BODY	"<html><body><h1>400 Bad Request</h1>" \
						  		"<p>The server could not understand the request due to invalid syntax.</p>" \
						  		"</body></html>"

//-----------------------------403-----------------------------
#define FORBIDDEN_ERROR "HTTP/1.1 403 Forbidden\r\n" \
						"Content-Type: text/html\r\n\r\n"

#define FORBIDDEN_ERROR_BODY	"<html><body><h1>403 Forbidden</h1>" \
								"<p>You do not have permission to access the requested resource.</p>" \
								"</body></html>"

//-----------------------------404-----------------------------
#define NOT_FOUND_ERROR "HTTP/1.1 404 Not Found\r\n" \
						"Content-Type: text/html\r\n\r\n"

#define NOT_FOUND_ERROR_BODY	"<html><body><h1>404 Not Found</h1>" \
								"<p>The requested resource could not be found on this server.</p>" \
								"</body></html>"

//-----------------------------405-----------------------------
#define METHOD_NOT_ALLOWED_ERROR "HTTP/1.1 405 Method Not Allowed\r\n" \
								 "Content-Type: text/html\r\n\r\n"

#define METHOD_NOT_ALLOWED_ERROR_BODY	"<html><body><h1>405 Method Not Allowed</h1>" \
								 		"<p>The requested method is not allowed for the URL.</p>" \
								 		"</body></html>"

//-----------------------------500-----------------------------
#define INTERNAL_SERVER_ERROR "HTTP/1.1 500 Internal Server Error\r\n" \
							  "Content-Type: text/html\r\n\r\n"

#define INTERNAL_SERVER_ERROR_BODY	"<html><body><h1>500 Internal Server Error</h1>" \
							  		"<p>The server encountered an internal error and could not complete your request.</p>" \
							  		"</body></html>"

//-----------------------------415-----------------------------
#define UNSUPPORTED_MEDIA_TYPE_ERROR "HTTP/1.1 415 Unsupported Media Type\r\n" \
									 "Content-Type: text/html\r\n\r\n"

#define UNSUPPORTED_MEDIA_TYPE_ERROR_BODY	"<html><body><h1>415 Unsupported Media Type</h1>" \
											"<p>The server does not support the media type transmitted in the request.</p>" \
											"</body></html>"

//-----------------------------413-----------------------------
#define PAYLOAD_TOO_LARGE_ERROR "HTTP/1.1 413 Payload Too Large\r\n" \
                                "Content-Type: text/html\r\n\r\n"

#define PAYLOAD_TOO_LARGE_ERROR_BODY "<html><body><h1>413 Payload Too Large</h1>" \
                                     "<p>The request is too large for the server to process.</p>" \
                                     "</body></html>"


//-----------------------------200-----------------------------
#define HTTP_SUCCESS	"HTTP/1.1 200 OK\r\n" \
						"Content-Type: text/html\r\n\r\n"

#define FILE_UPLOAD_SUCCESS "<html><body><h1>File uploaded successfully.</h1>" \
							"</body></html>"

#define TEXT_UPLOAD_SUCCESS "<html><body><h1>Text data submitted successfully.</h1>" \
							"</body></html>"

#define FILE_DELETE_SUCCESS "<html><body><h1>File deleted successfully.</h1>" \
							"</body></html>"

