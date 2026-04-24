@echo off
echo ==============================================
echo   Starting Smart Sorting Studio (Web Mode)
echo ==============================================
echo.

echo [1/2] Starting Node.js Backend API...
start "Backend API" cmd /k "cd web\backend && node server.js"

echo [2/2] Starting Vite React Frontend...
start "Frontend UI" cmd /k "cd web\frontend && npm run dev -- --open"

echo.
echo Both servers are launching in separate windows!
echo The Web UI will automatically open in your default browser.
echo You can safely close those terminal windows to stop the servers later.
pause
