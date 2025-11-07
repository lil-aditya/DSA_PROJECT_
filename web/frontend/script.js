const form = document.getElementById('simForm');
const output = document.getElementById('output');

form.addEventListener('submit', async (e) => {
  e.preventDefault();
  output.textContent = "Running simulation...";
  const formData = new FormData(form);
  const res = await fetch('http://127.0.0.1:8000/simulate', {
    method: 'POST',
    body: formData
  });
  const data = await res.json();
  if (data.error) {
    output.textContent = "Error: " + data.error;
  } else {
    output.textContent = data.stdout + (data.stderr ? "\n" + data.stderr : "");
  }
});
