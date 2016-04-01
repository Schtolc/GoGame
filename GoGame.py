from cgi import parse_qs, escape

playerTeam = 0

def application (environ, start_response):

    # Sorting and stringifying the environment key, value pairs
    q = parse_qs(environ['QUERY_STRING'])
    if 'erase' in q:
        global playerTeam
        playerTeam = 0
    response_body = str(playerTeam)
    playerTeam += 2;
    status = '200 OK'
    response_headers = [
        ('Content-Type', 'text/plain'),
        ('Content-Length', str(len(response_body)))
    ]
    start_response(status, response_headers)

    return [response_body]
