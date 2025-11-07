from fastapi import FastAPI, Form
from fastapi.responses import JSONResponse
import subprocess, shlex
from pathlib import Path

app = FastAPI()

EXE_PATH = Path(__file__).resolve().parents[2] / "build" / "dsa_project.exe"

@app.post("/simulate")
async def simulate(username: str = Form(...), priority: str = Form(...), dest: int = Form(...)):
    if not EXE_PATH.exists():
        return JSONResponse({"error": f"Executable not found at {EXE_PATH}"}, status_code=500)

    cmd = f'"{EXE_PATH}" "{username}" "{priority}" "{dest}"'
    proc = subprocess.run(shlex.split(cmd), capture_output=True, text=True)
    return {"stdout": proc.stdout, "stderr": proc.stderr, "returncode": proc.returncode}
