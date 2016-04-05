from cgi import parse_qs, escape

playerAmount = 0
playerKeys = []
lastStep = ''
currentPlayer = ''
playerDict = {}

def application (environ, start_response):
   
    response_body = ""
    q = parse_qs(environ['QUERY_STRING'])
    
    #?newlobby=4
    if 'newlobby' in q:
        global playerAmount
        amount = ''.join(q['newlobby'])
        playerAmount = int(amount)

    elif 'waiting' in q:
        global playerAmount, playerKeys
        if len(playerKeys) == playerAmount:
            response_body += "ready"
        else: 
            response_body += "waiting"

    #?isLocked=token
    elif 'isLocked' in q:
        global currentPlayer
        player = ''.join(q['isLocked'])

        if player == currentPlayer:
             response_body += "Unlocked"
        else: 
             response_body += "Locked"

    #?register=token
    elif 'register' in q:
        global playerKeys, playerDict
        
        if (len(playerKeys) == playerAmount):
            response_body += str(-1)
        else:
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

    #?passstep=token
    elif 'passstep' in q:
        global lastStep, playerDict
        player = ''.join(q['passstep'])

        if playerKeys.index(player) == len(playerKeys)-1:
            currentPlayer = playerKeys[0]
        else:
            currentPlayer = playerKeys[playerKeys.index(player)+1]
    
    status = '200 OK'
    response_headers = [
        ('Content-Type', 'text/plain'),
        ('Content-Length', str(len(response_body)))
    ]
    start_response(status, response_headers)

    return [response_body]
