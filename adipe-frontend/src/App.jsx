import React, { useState, useEffect } from "react";

export default function App() {
  const [message, setMessage] = useState("");
  const [priority, setPriority] = useState("Low");
  const [messages, setMessages] = useState([]);
  const [events, setEvents] = useState([]);
  const [darkMode, setDarkMode] = useState(false);
  const [sendingIds, setSendingIds] = useState(new Set());
  const [destination, setDestination] = useState(5);
  const [connected, setConnected] = useState(false);
  const [sender, setSender] = useState("Admin");

  const priorityColors = {
    Low: "bg-green-500",
    Medium: "bg-yellow-500",
    High: "bg-red-500",
  };

  // ✅ Apply dark class to <html>
  useEffect(() => {
    if (darkMode) document.documentElement.classList.add("dark");
    else document.documentElement.classList.remove("dark");
  }, [darkMode]);

  // Poll selected node events for live updates (every 750ms)
  useEffect(() => {
    let mounted = true;
    const poll = async () => {
      try {
        const res = await fetch(`http://localhost:${8080 + destination}/events`);
        if (!res.ok) return;
        const arr = await res.json();
        // arr is an array of JSON strings created by the backend; parse them
        const parsed = arr.map((s) => {
          try {
            return JSON.parse(s);
          } catch (e) {
            return { event: String(s) };
          }
        });
        if (mounted) {
          setEvents(parsed.reverse()); // newest first
          setConnected(true);
        }
      } catch (e) {
        // network or CORS error; ignore silently
        if (mounted) setConnected(false);
      }
    };
    poll();
    const id = setInterval(poll, 750);
    return () => {
      mounted = false;
      clearInterval(id);
    };
  }, [destination]);

  const cyclePriority = () => {
    if (priority === "Low") setPriority("Medium");
    else if (priority === "Medium") setPriority("High");
    else setPriority("Low");
  };

  const handleSubmit = (e) => {
    e.preventDefault();
    if (!message.trim()) return;
    // keep UI list
    setMessages([{ text: message, priority }, ...messages]);

    // map priority to numeric urgency for the backend packet
    const urgencyMap = { Low: 10, Medium: 50, High: 90 };
    const pkt = {
      id: `ui_${Date.now()}`,
      urgency: urgencyMap[priority] || 10,
      data: message,
      senderID: "Node0",
      signature: 0,
      destinationID: destination
    };

    // send to selected node's backend dev endpoint (no signature verification) so the node receives it directly
    fetch(`http://localhost:${8080 + destination}/packet-dev`, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(pkt),
    }).catch((err) => {
      console.warn("Failed to POST packet to backend:", err);
    });

    setMessage("");
  };

  // Send a message object to the backend /packet-dev endpoint
  const sendMessage = async (msg) => {
    const urgencyMap = { Low: 10, Medium: 50, High: 90 };
    const id = `ui_${Date.now()}`;
    const pkt = {
      id,
      urgency: urgencyMap[msg.priority] || 10,
      data: msg.text,
      senderID: "Node0",
      signature: 0,
      destinationID: destination,
    };

    // optimistic UI: mark as sending
    setSendingIds((s) => new Set([...s, id]));

    try {
      await fetch(`http://localhost:${8080 + destination}/packet-dev`, {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify(pkt),
      });
      // optional: add a small feedback entry to events panel locally
      setEvents((prev) => [{ nodeID: destination, event: `Sent '${msg.text}' to network` }, ...prev]);
    } catch (err) {
      console.warn("Failed to send message:", err);
      setEvents((prev) => [{ nodeID: 0, event: `Failed to send '${msg.text}'` }, ...prev]);
    } finally {
      setSendingIds((s) => {
        const copy = new Set([...s]);
        copy.delete(id);
        return copy;
      });
    }
  };

  return (
    <div className="h-screen w-screen flex flex-col items-center justify-center bg-gradient-to-br from-indigo-900 via-gray-900 to-slate-900 text-gray-100 transition-colors duration-500 overflow-hidden relative">

      {/* 🌗 Dark / Light Toggle */}
      <button
        onClick={() => setDarkMode(!darkMode)}
        className="absolute top-5 right-5 px-4 py-2 text-sm rounded-lg border border-gray-400 dark:border-gray-600 hover:bg-gray-200 dark:hover:bg-gray-800 transition"
      >
        {darkMode ? "☀️ Light Mode" : "🌙 Dark Mode"}
      </button>

      <div className="w-full max-w-4xl mt-6 grid grid-cols-2 gap-6">
        {/* Left: Inject Packet Form */}
        <div className="bg-gray-800/40 dark:bg-gray-900/40 shadow-2xl rounded-2xl p-8 text-left">
          <h2 className="text-2xl font-bold mb-4">Inject New Packet</h2>

          <label className="text-sm text-gray-300">Sender (User)</label>
          <select value={sender} onChange={(e) => setSender(e.target.value)} className="w-full mb-3 mt-1 rounded px-3 py-2 bg-gray-700">
            <option>Admin</option>
            <option>UserA</option>
            <option>UserB</option>
          </select>

          <label className="text-sm text-gray-300">Priority (Urgency)</label>
          <select value={priority} onChange={(e) => setPriority(e.target.value)} className="w-full mb-3 mt-1 rounded px-3 py-2 bg-gray-700">
            <option value="High">High (20)</option>
            <option value="Medium">Medium (10)</option>
            <option value="Low">Low (5)</option>
          </select>

          <label className="text-sm text-gray-300">Destination Node</label>
          <select value={destination} onChange={(e) => setDestination(Number(e.target.value))} className="w-full mb-3 mt-1 rounded px-3 py-2 bg-gray-700">
            <option value={0}>0</option>
            <option value={1}>1</option>
            <option value={2}>2</option>
            <option value={3}>3</option>
            <option value={4}>4</option>
            <option value={5}>5</option>
          </select>

          <label className="text-sm text-gray-300">Packet Data</label>
          <input value={message} onChange={(e) => setMessage(e.target.value)} className="w-full mb-4 mt-1 rounded px-3 py-2 bg-gray-700" />

          <div className="mt-4">
            <button onClick={handleSubmit} className="w-full px-4 py-3 bg-blue-600 hover:bg-blue-700 rounded text-white font-semibold">Inject Packet</button>
          </div>
        </div>

        {/* Right: Live C++ Network Log */}
        <div className="bg-gray-900/40 dark:bg-gray-800/60 shadow rounded-lg p-6">
          <div className="flex items-center justify-between mb-4">
            <h2 className="text-2xl font-bold">Live C++ Network Log</h2>
            <div className="flex items-center gap-2">
              <span className={`w-3 h-3 rounded-full ${connected ? 'bg-green-400' : 'bg-red-500'}`}></span>
              <span className="text-sm text-gray-300">{connected ? 'ONLINE - C++/Python API detected.' : 'OFFLINE - C++/Python API not detected.'}</span>
            </div>
          </div>

          <div className="bg-black/60 text-gray-200 p-4 rounded h-72 overflow-auto font-mono text-sm">
            {connected ? (
              events.length === 0 ? (
                <div>No events yet</div>
              ) : (
                events.map((e, i) => (
                  <div key={i} className="mb-2">
                    <div className="text-xs text-gray-400">Node {e.nodeID}</div>
                    <div>{e.event}</div>
                  </div>
                ))
              )
            ) : (
              <div className="text-red-400">Error fetching log: Failed to fetch</div>
            )}
          </div>
        </div>
      </div>
    </div>
  );
}
