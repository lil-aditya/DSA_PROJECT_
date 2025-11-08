# # from fastapi import FastAPI, Form
# # from fastapi.responses import JSONResponse
# # import subprocess, shlex
# # from pathlib import Path

# # app = FastAPI()

# # EXE_PATH = Path(__file__).resolve().parents[2] / "build" / "dsa_project.exe"

# # @app.post("/simulate")
# # async def simulate(username: str = Form(...), priority: str = Form(...), dest: int = Form(...)):
# #     if not EXE_PATH.exists():
# #         return JSONResponse({"error": f"Executable not found at {EXE_PATH}"}, status_code=500)

# #     cmd = f'"{EXE_PATH}" "{username}" "{priority}" "{dest}"'
# #     proc = subprocess.run(shlex.split(cmd), capture_output=True, text=True)
# #     return {"stdout": proc.stdout, "stderr": proc.stderr, "returncode": proc.returncode}
# import uvicorn
# import requests
# from fastapi import FastAPI, Request
# from fastapi.responses import JSONResponse
# from fastapi.middleware.cors import CORSMiddleware
# from pydantic import BaseModel
# import time

# # --- Configuration ---
# # The URL of your C++ network's "Node 0"
# # This is the "injection point" for new packets.
# CPP_NODE_0_URL = "http://localhost:8080"


# # --- FastAPI Application Setup ---
# app = FastAPI()

# # --- CRITICAL: Add CORS Middleware ---
# # This allows your index.html (on file://) to
# # talk to this server (on http://localhost:8000).
# # Without this, your browser will block all requests.
# app.add_middleware(
#     CORSMiddleware,
#     allow_origins=["*"], # Allows all origins
#     allow_credentials=True,
#     allow_methods=["*"], # Allows all methods (GET, POST, etc.)
#     allow_headers=["*"], # Allows all headers
# )

# # --- Pydantic Model ---
# # This defines the structure of the JSON we expect from the UI
# # It matches the DataPacket struct (minus the signature)
# class PacketInjectRequest(BaseModel):
#     id: str
#     urgency: int
#     data: str
#     senderID: str
#     destinationID: int

# # --- API Endpoints ---

# @app.get("/check_cpp_status")
# async def check_cpp_status():
#     """
#     Health check endpoint for the UI.
#     Tries to connect to the C++ Node 0 server.
#     """
#     try:
#         # Make a GET request to the /check endpoint on the C++ server
#         response = requests.get(f"{CPP_NODE_0_URL}/check", timeout=0.5)
        
#         if response.status_code == 200:
#             return {"status": "ONLINE"}
#         else:
#             return {"status": "OFFLINE", "error": f"C++ server responded with {response.status_code}"}
            
#     except requests.exceptions.ConnectionError:
#         # This error means the C++ executable isn't running.
#         return {"status": "OFFLINE", "error": "C++ server is not running or refused connection."}
#     except Exception as e:
#         return {"status": "OFFLINE", "error": str(e)}

# @app.post("/inject")
# async def inject_packet(packet_request: PacketInjectRequest):
#     """
#     Receives packet data from the UI, signs it (in C++),
#     and injects it into the C++ network.
#     """
#     try:
#         # Forward the UI's request to the C++ Node 0's /inject endpoint
#         # The C++ server will handle signing and starting the route.
#         cpp_url = f"{CPP_NODE_0_URL}/inject"
        
#         # .dict() converts the Pydantic model to a Python dictionary
#         response = requests.post(cpp_url, json=packet_request.model_dump()) # Use .model_dump() for modern Pydantic

#         if response.status_code == 200:
#             return response.json()
#         else:
#             return JSONResponse(
#                 content={"error": f"C++ server returned error: {response.status_code}", "details": response.text},
#                 status_code=response.status_code
#             )
            
#     except requests.exceptions.ConnectionError:
#         return JSONResponse(
#             content={"error": "Failed to connect to C++ network engine. Is it running?"},
#             status_code=503 # 503 Service Unavailable
#         )

# @app.get("/log")
# async def get_log():
#     """
#     'Poll' endpoint for the UI to get live log updates
#     from the C++ network.
#     """
#     try:
#         # Make a GET request to the C++ server's /log endpoint
#         cpp_url = f"{CPP_NODE_0_URL}/log"
#         response = requests.get(cpp_url)

#         if response.status_code == 200:
#             # Forward the JSON list of logs directly to the UI
#             return response.json()
#         else:
#             return JSONResponse(
#                 content={"error": f"C++ server returned error: {response.status_code}"},
#                 status_code=response.status_code
#             )

#     except requests.exceptions.ConnectionError:
#         return JSONResponse(
#             content={"error": "Failed to connect to C++ network engine."},
#             status_code=503
#         )

# # --- Main execution to run the server ---
# if __name__ == "__main__":
#     print("Starting Python API server on http://localhost:8000")
#     uvicorn.run("server:app", host="0.0.0.0", port=8000, reload=True)
import uvicorn
import requests
from fastapi import FastAPI, Form
from fastapi.responses import JSONResponse
from fastapi.middleware.cors import CORSMiddleware
import json

# --- Configuration ---
app = FastAPI()

# This is the address of your C++ server's Node 0
CPP_NODE_0_URL = "http://127.0.0.1:8080"

# --- CORS Middleware ---
# This allows your index.html (on a file:// path) to talk to this
# Python server (on http://127.0.0.1:8000).
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"], # Allows all origins (for file://)
    allow_credentials=True,
    allow_methods=["*"], # Allows all methods (GET, POST)
    allow_headers=["*"], # Allows all headers
)

# --- API Endpoints ---

@app.get("/status")
async def get_status():
    """
    Checks if the Python API and C++ network are online.
    This is what the "Status Light" on the UI calls.
    """
    try:
        # Check C++ Node 0's /check endpoint
        response = requests.get(f"{CPP_NODE_0_URL}/check", timeout=1)
        if response.status_code == 200:
            return {"status": "online"}
    except requests.exceptions.ConnectionError:
        pass # Fall through to the error response
    
    return JSONResponse(content={"status": "offline"}, status_code=503)

@app.get("/log")
async def get_log():
    """
    Fetches the shared C++ network log from Node 0.
    This is what the "Live C++ Network Log" box calls.
    """
    try:
        # Ask C++ Node 0 for its log
        response = requests.get(f"{CPP_NODE_0_URL}/log", timeout=1)
        response.raise_for_status() # Raise error if status isn't 200
        
        # The C++ server returns a JSON list of strings
        log_data = response.json() 
        return {"log": log_data}
        
    except requests.exceptions.RequestException as e:
        return {"log": [f"Error fetching C++ log: {e}"]}

@app.post("/inject")
async def inject_packet(
    senderID: str = Form(...),
    urgency: int = Form(...),
    destinationID: int = Form(...),
    data: str = Form(...)
):
    """
    Receives packet data from the UI and "injects" it into C++ Node 0.
    This endpoint matches the index.html <form> fields.
    """
    
    # Create the JSON payload to send to the C++ server
    packet_data = {
        "id": f"{senderID.lower()}_ui_packet",
        "urgency": urgency,
        "data": data,
        "senderID": senderID,
        "signature": 0, # The C++ node will generate this
        "destinationID": destinationID
    }
    
    try:
        # Send the packet to C++ Node 0's /inject endpoint
        response = requests.post(f"{CPP_NODE_0_URL}/inject", json=packet_data, timeout=3)
        response.raise_for_status()
        
        # Return the C++ server's response to the UI
        return response.json()
        
    except requests.exceptions.RequestException as e:
        return JSONResponse(content={"detail": f"Failed to connect to C++ network: {e}"}, status_code=503)

# --- Main execution to run the server ---
if __name__ == "__main__":
    print("Starting Python API server on http://localhost:8000")
    uvicorn.run("server:app", host="127.0.0.1", port=8000, reload=True)

### Your Next Steps

# 1.  **Restart Python Server:** Go back to **Terminal 2 (MINGW64)**. It should have auto-restarted (because of `--reload`). If not, just run it again:
#     ```bash
#     uvicorn server:app --reload