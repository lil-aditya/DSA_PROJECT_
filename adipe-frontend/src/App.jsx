import React, { useState, useEffect } from "react";

export default function App() {
  const [message, setMessage] = useState("");
  const [priority, setPriority] = useState("Low");
  const [messages, setMessages] = useState([]);
  const [darkMode, setDarkMode] = useState(false);

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

  const cyclePriority = () => {
    if (priority === "Low") setPriority("Medium");
    else if (priority === "Medium") setPriority("High");
    else setPriority("Low");
  };

  const handleSubmit = (e) => {
    e.preventDefault();
    if (!message.trim()) return;
    setMessages([{ text: message, priority }, ...messages]);
    setMessage("");
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

      {/* 💬 Main Card */}
      <div className="bg-gray-800/40 dark:bg-gray-900/40 shadow-2xl rounded-2xl p-10 w-full max-w-2xl text-center backdrop-blur-xl transition-all duration-500">
        <h1 className="text-3xl font-bold mb-6">
          ADIPE — Priority Message Manager
        </h1>

        {/* Input Form */}
        <form onSubmit={handleSubmit} className="flex flex-col gap-4">
          <textarea
            className="w-full p-3 rounded-lg border border-gray-500/50 dark:border-gray-700 bg-gray-50/10 dark:bg-gray-800/20 focus:outline-none focus:ring-2 focus:ring-blue-500 transition"
            rows="3"
            placeholder="Enter your message..."
            value={message}
            onChange={(e) => setMessage(e.target.value)}
          ></textarea>

          <div className="flex items-center justify-between">
            <button
              type="button"
              onClick={cyclePriority}
              className={`px-5 py-2 rounded-lg text-white font-semibold ${priorityColors[priority]} hover:opacity-90 transition`}
            >
              Priority: {priority}
            </button>

            <button
              type="submit"
              className="px-5 py-2 bg-blue-600 hover:bg-blue-700 rounded-lg text-white font-semibold transition"
            >
              Add Message
            </button>
          </div>
        </form>
      </div>

      {/* 🧾 Messages List */}
      <div className="mt-6 w-full max-w-2xl space-y-3 px-4 overflow-y-auto">
        {messages.map((msg, idx) => (
          <div
            key={idx}
            className={`p-4 rounded-lg shadow-md flex justify-between items-center ${priorityColors[msg.priority]} text-white`}
          >
            <span className="font-medium">{msg.text}</span>
            <span className="text-sm font-semibold">{msg.priority}</span>
          </div>
        ))}
      </div>
    </div>
  );
}
