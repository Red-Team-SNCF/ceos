# CEOS - Basic Mythic Implant in C

Ceos is a basic Windows implant written in C interfaceable with the Mythic C2 framework. 

This repo was made to showcase the usage of a translator container for low-level languages implant for Mythic.
A blogpost explains in great detail how (and why) this project was conceived.

More info on our blog post: [How to build your own mythic agent in C](https://red-team-sncf.github.io/how-to-create-your-own-mythic-agent-in-c.html)

## Install Ceos

Once Mythic is installed and running : 
```
./mythic-cli install github https://github.com/Red-Team-SNCF/ceos
```

## Detection

A YARA rule to detect Ceos is provided for detection purposes.

## Communication protocol
### HEADER - Implant to C2

| Key     | Key Len (bytes)   | Type       |
|---------|-------------------|------------|
| UUID    | 36                | Str (char*)|
| Action  | 1                 | UInt32      |


### HEADER - C2 to Implant

| Key     | Key Len (bytes)   | Type       |
|---------|-------------------|------------|
|Action   | 1                 | Int32      |



UUID|BODY|

#### Checkin - Implant to C2

Expected : 
```
a21bab2e-462e-49ab-9800-fbedaf53ad15
{
    "action":"checkin",
    "uuid":"a21bab2e-462e-49ab-9800-fbedaf53ad15",
    "ip":"127.0.0.1",
    "os":"win",
    "arch":"x64",
    "hostname":"PC",
    "user":"bob",
    "domain":"domain.com",
    "pid":123,
    "processname":"malware.exe",
}
```

| Key           | Key Len (bytes)   | Type        |
|---------------|-------------------|-------------|
| UUID          | 36                | Str (char*) |
| Size IP       | 4                 | Uint32      |
| IP            | Size IP           | Str (char*) |
| Size OS       | 4                 | Uint32      |
| OS            | Size OS           | Str (char*) |
| Architecture  | 1                 | Int         |
| Size Hostname | 4                 | Uint32      |
| HostName      | Size Hostname     | Str (char*) |
| Size Username | 4                 | Uint32      |
| Username      | Size Username     | Str (char*) |
| Size Domaine  | 4                 | Uint32      |
| Domaine       | Size Domaine      | Str (char*) |
| PID           | 4                 | Uint32      |
| Size ProcessN | 4                 | Uint32      |
| Process Name  | Size Process Name | Str (char*) |
| Size ExternIP | 4                 | Uint32      |
| Extern IP     | Size Extern IP    | Str (char*) |


### Checkin - C2 to Implant 

| Key           | Key Len (bytes)   | Type        |
|---------------|-------------------|-------------|
| New UUID      | 36                | Str (char*) |
| Status        | 1                 | Byte        |




### GetTasking - Implant to C2
```
Expected: 
{
	"action": "get_tasking",
	"tasking_size": 1, //indicate the maximum number of tasks you want back
}
```

| Key           | Key Len (bytes)   | Type        |
|---------------|-------------------|-------------|
| Number tasks  | 4                 | Uint32      |


### GetTasking - C2 to Implant

```
Expected : 
{
	"action": "get_tasking",
	"tasks": [
		{
			"command": "command name",
			"parameters": "command param string",
			"timestamp": 1578706611.324671, //timestamp provided to help with ordering
			"id": "task uuid",
		}
	],
}
```

| Key           | Key Len (bytes)   | Type        |
|---------------|-------------------|-------------|
| NumberOfTasks | 4                 | Uint32      |
| Size Of Task1 | 4                 | Uint32      |
| Task1 CMD     | 1                 | Int         |
| Task1 UUID    | 36                | Str (char*) |
| Task1 LenPara1| 4                 | Uint32      |
| Task1 Param1  | LenParam1 Task1   | Str(char*)  |





### Post Response Header - Implant to C2 

| Key           | Key Len (bytes)   | Type        |
|---------------|-------------------|-------------|
| Number Resp   | 4                 | Uint32      |


### Post Response Header - C2 to Implant 

| Key           | Key Len (bytes)   | Type        |
|---------------|-------------------|-------------|
| Number Resp   | 4                 | Uint32      |



### Post Response Classic output return - Implant to C2

```
Expected : 
{
	"action": "post_response",
	"responses": [
		{
			"task_id": "uuid of task",
			... response message (see below)
		},
		{
			"task_id": "uuid of task",
			... response message (see below)
		}
	], 

}
```
| Key           | Key Len (bytes)   | Type        |
|---------------|-------------------|-------------|
| UUID Resp 1   | 36                | Str (char*) |
| Size Output R1| 4                 | Uint32      |
| Output R1     | Size Output       | Bytes       |
| Status R1     | 1                 | Int         |




### Post Response Classic output return - C2 to Implant

```
Expected : 
{
	"action": "post_response",
	"responses": [
		{
			"task_id": UUID,
			"status": "success" or "error",
			"error": 'error message if it exists'
		}
	]
}
```

| Key           | Key Len (bytes)   | Type        |
|---------------|-------------------|-------------|
| Statut Resp1  | 1                 | Int         | 

