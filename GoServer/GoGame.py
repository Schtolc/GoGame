from cgi import parse_qs, escape

playerKeys = []
lastStep = ''
currentPlayer = ''
playerDict = {}

def application (environ, start_response):
   
    response_body = ""
    q = parse_qs(environ['QUERY_STRING'])
    
    #?isLocked=token
    if 'isLocked' in q:
        global currentPlayer
        player = ''.join(q['isLocked'])

        if player == currentPlayer:
             response_body += "Unlocked"
        else: 
             response_body += "Locked"

    #?register=token
    elif 'register' in q:
        global playerKeys, playerDict
        player = ''.join(q['register'])

        if player not in playerKeys:
             if not playerKeys:
                 currentPlayer = player
             playerKeys.append(player)
             playerDict[player] = False
        response_body += str(playerKeys.index(player))

    #?makestep=x0y0t0ptoken
    elif 'makestep' in q:
        global lastStep, playerDict, playerKeys, currentPlayer
        query = ''.join(q['makestep'])
        new_step = query[:query.index('p')]
        player = query[query.index('p')+1:]

        lastStep = new_step
        for key in playerDict:
            if key != player:
                 playerDict[key]=True

        if playerKeys.index(player) == len(playerKeys)-1:
            currentPlayer = playerKeys[0]
        else:
            currentPlayer = playerKeys[playerKeys.index(player)+1]

    #?getstep=token
    elif 'getstep' in q:
        global lastStep, playerDict
        player = ''.join(q['getstep'])

        if playerDict[player] == True:
            response_body += lastStep
            playerDict[player] = False
        else:
            response_body += 'None'
    
    status = '200 OK'
    response_headers = [
        ('Content-Type', 'text/plain'),
        ('Content-Length', str(len(response_body)))
    ]
    start_response(status, response_headers)

    return [response_body]
