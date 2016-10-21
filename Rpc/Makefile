#make: processor.c comm_svc.c receiver.c comm_clnt.c
#	gcc processor.c comm_svc.c -o server -lnsl
#	gcc receiver.c comm_clnt.c -o client -lnsl

#clean:
#	rm server client

CLIENT = receiver
SERVER = processor

SOURCES_CLNT.c = 
SOURCES_CLNT.h = 
SOURCES_SVC.c =    
SOURCES_SVC.h = 
SOURCES.x = comm.x

TARGETS_SVC.c = comm_svc.c processor.c    
TARGETS_CLNT.c = comm_clnt.c receiver.c     
TARGETS = comm.h  comm_clnt.c comm_svc.c  receiver.c processor.c
NOTUSER = comm.h  comm_clnt.c comm_svc.c

OBJECTS_CLNT = $(SOURCES_CLNT.c:%.c=%.o) $(TARGETS_CLNT.c:%.c=%.o)
OBJECTS_SVC = $(SOURCES_SVC.c:%.c=%.o) $(TARGETS_SVC.c:%.c=%.o)
# Compiler flags 

CFLAGS += -g
LDLIBS += 
#-lnsl
RPCGENFLAGS = 

# Targets 

all : $(CLIENT) $(SERVER)

$(TARGETS) : $(SOURCES.x) 
	rpcgen $(RPCGENFLAGS) $(SOURCES.x)

$(OBJECTS_CLNT) : $(SOURCES_CLNT.c) $(SOURCES_CLNT.h) $(TARGETS_CLNT.c) 

$(OBJECTS_SVC) : $(SOURCES_SVC.c) $(SOURCES_SVC.h) $(TARGETS_SVC.c) 

$(CLIENT) : $(OBJECTS_CLNT) 
	$(LINK.c) -o $(CLIENT) $(OBJECTS_CLNT) $(LDLIBS) 

$(SERVER) : $(OBJECTS_SVC) 
	$(LINK.c) -o $(SERVER) $(OBJECTS_SVC) $(LDLIBS)

 clean:
	 $(RM) core $(NOTUSER) $(OBJECTS_CLNT) $(OBJECTS_SVC) $(CLIENT) $(SERVER) secrets.out


