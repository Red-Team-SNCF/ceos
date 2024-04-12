from translator.utils import *
import ipaddress

def checkIn(data):
    
    # Retrieve UUID
    uuid = data[:36]
    data = data[36:]
    print(data)
    # Retrieve IPs
    numIPs = int.from_bytes(data[0:4])
    data = data[4:]
    i = 0
    IPs = []
    print(numIPs)
    while i < numIPs:
        ip = data[:4]
        data = data[4:]
        addr = str(ipaddress.ip_address(ip))
        IPs.append(addr)
        i += 1
        
    print(IPs)
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
    print(hostname)

    # Retrieve Username
    username, data = getBytesWithSize(data)
    print(username)

    # Retrieve Domaine
    domain, data = getBytesWithSize(data)
    print(domain)
    

    # Retrieve PID
    pid = int.from_bytes(data[0:4])
    data = data[4:]
    print(pid)

    # Retrieve Process Name
    processName, data = getBytesWithSize(data)
    print(processName)

    #Retrieve External IP
    externalIP, data = getBytesWithSize(data)
    print(externalIP)

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

    print(dataJson)
    
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
    print(jsonTask)


    jsonTask["completed"] = True

    resTaks.append(jsonTask)

    # for task in resTaks:
    #     for task2 in resTaks:
    #         if task == task2:
    #             continue
    #         if task2["task_id"] == task["task_id"]:
    #             task["user_output"] += task2["user_output"]
    #         resTaks.remove(task2)
    
    dataJson = {
        "action": "post_response",
        "responses": resTaks
    }
    return dataJson
