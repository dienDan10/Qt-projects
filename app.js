// ===== State =====
let currentProject = null;
let doneProjects = new Set(JSON.parse(localStorage.getItem('qt-done') || '[]'));

// ===== Init =====
function init() {
  updateProgress();
  updateAllChecks();
  // Show first project by default
  showProject('01');
}

// ===== Navigation =====
function showProject(id) {
  currentProject = id;

  // Update nav active state
  document.querySelectorAll('.nav-item').forEach(el => {
    el.classList.toggle('active', el.dataset.id === id);
  });

  const p = PROJECTS[id];
  if (!p) return;

  const isDone = doneProjects.has(id);

  document.getElementById('projectContent').innerHTML = renderProject(p, isDone);
}

// ===== Render =====
function renderProject(p, isDone) {
  const levelClass = `level-${p.level}`;

  return `
<div class="project-page">

  <!-- Hero -->
  <div class="project-hero">
    <div class="hero-eyebrow">
      <span class="hero-num">Project ${p.num}</span>
      <span class="level-badge ${levelClass}">${p.levelLabel}</span>
      ${p.workRelevant ? '<span class="work-badge">🎯 gần công việc</span>' : ''}
    </div>
    <h1 class="project-title">${p.title}</h1>
    <p class="project-desc">${p.desc}</p>
    <div class="hero-meta">
      <div class="meta-item"><span class="meta-icon">⏱</span> ${p.time}</div>
      <div class="meta-item"><span class="meta-icon">📅</span> ${p.when}</div>
    </div>
    <button class="done-btn ${isDone ? 'is-done' : ''}" onclick="toggleDone('${p.num}')">
      ${isDone ? '✓ Đã hoàn thành' : '○ Đánh dấu hoàn thành'}
    </button>
  </div>

  <!-- Requirements -->
  <div class="section">
    <div class="section-title">Requirements</div>
    <div class="req-list">
      ${p.requirements.map(r => `
        <div class="req-item">
          <span class="req-icon">▸</span>
          <span>${r}</span>
        </div>
      `).join('')}
    </div>
  </div>

  <!-- Knowledge -->
  <div class="two-col" style="margin-bottom: 32px;">
    <div class="info-card">
      <div class="info-card-label">🔴 Cần biết trước</div>
      <div class="tags" style="margin-top: 4px;">
        ${p.prereqs.map(t => `<span class="tag tag-required">${t}</span>`).join('')}
      </div>
    </div>
    <div class="info-card">
      <div class="info-card-label">🟢 Sẽ học được khi làm</div>
      <div class="tags" style="margin-top: 4px;">
        ${p.learns.map(t => `<span class="tag tag-learn">${t}</span>`).join('')}
      </div>
    </div>
  </div>

  <!-- Tools -->
  <div class="section">
    <div class="section-title">Tools & APIs</div>
    <div class="tags">
      ${p.tools.map(t => `<span class="tag tag-tool">${t}</span>`).join('')}
    </div>
  </div>

  <!-- Architecture -->
  <div class="section">
    <div class="section-title">Architecture</div>
    <div class="arch-box">${p.architecture}</div>
  </div>

  <!-- File Structure -->
  <div class="section">
    <div class="section-title">File Structure</div>
    <div class="file-tree">${p.fileTree}</div>
  </div>

  <!-- Steps -->
  <div class="section">
    <div class="section-title">Các bước thực hiện</div>
    <div class="steps">
      ${p.steps.map((s, i) => `
        <div class="step">
          <div class="step-num">${String(i + 1).padStart(2, '0')}</div>
          <div class="step-body">
            <div class="step-title">${s.title}</div>
            <div class="step-desc">${s.desc}</div>
          </div>
        </div>
      `).join('')}
    </div>
  </div>

  <!-- Notes -->
  <div class="section">
    <div class="section-title">Lưu ý & Tips</div>
    <div class="notes">
      ${p.notes.map(n => `
        <div class="note note-${n.type}">
          <span class="note-icon">${n.icon}</span>
          <span>${n.text}</span>
        </div>
      `).join('')}
    </div>
  </div>

  <!-- Nav buttons -->
  <div style="display:flex; justify-content:space-between; margin-top: 40px; padding-top: 20px; border-top: 1px solid var(--border);">
    ${prevNextButtons(p.num)}
  </div>

</div>
  `;
}

function prevNextButtons(num) {
  const n = parseInt(num);
  const prev = n > 1 ? String(n - 1).padStart(2, '0') : null;
  const next = n < 11 ? String(n + 1).padStart(2, '0') : null;

  const prevBtn = prev
    ? `<button onclick="showProject('${prev}')" style="display:flex;align-items:center;gap:8px;padding:9px 16px;border-radius:6px;border:1px solid var(--border);background:transparent;color:var(--text-muted);font-size:13px;cursor:pointer;font-family:var(--font-sans);">← Project ${prev}: ${PROJECTS[prev].title}</button>`
    : `<span></span>`;

  const nextBtn = next
    ? `<button onclick="showProject('${next}')" style="display:flex;align-items:center;gap:8px;padding:9px 16px;border-radius:6px;border:1px solid var(--border);background:transparent;color:var(--text-muted);font-size:13px;cursor:pointer;font-family:var(--font-sans);">Project ${next}: ${PROJECTS[next].title} →</button>`
    : `<span></span>`;

  return prevBtn + nextBtn;
}

// ===== Done tracking =====
function toggleDone(id) {
  if (doneProjects.has(id)) {
    doneProjects.delete(id);
  } else {
    doneProjects.add(id);
  }
  localStorage.setItem('qt-done', JSON.stringify([...doneProjects]));
  updateProgress();
  updateAllChecks();

  // Re-render current project to update button state
  const btn = document.querySelector('.done-btn');
  if (btn) {
    const isDone = doneProjects.has(id);
    btn.textContent = isDone ? '✓ Đã hoàn thành' : '○ Đánh dấu hoàn thành';
    btn.classList.toggle('is-done', isDone);
  }

  // Update nav item
  const navItem = document.querySelector(`.nav-item[data-id="${id}"]`);
  if (navItem) {
    navItem.classList.toggle('done', doneProjects.has(id));
  }
}

function updateProgress() {
  const count = doneProjects.size;
  const pct = (count / 11) * 100;
  document.getElementById('progressCount').textContent = `${count} / 11`;
  document.getElementById('progressBar').style.width = `${pct}%`;
}

function updateAllChecks() {
  for (let i = 1; i <= 11; i++) {
    const id = String(i).padStart(2, '0');
    const check = document.getElementById(`check-${id}`);
    const navItem = document.querySelector(`.nav-item[data-id="${id}"]`);
    if (check) check.textContent = doneProjects.has(id) ? '✓' : '○';
    if (navItem) navItem.classList.toggle('done', doneProjects.has(id));
  }
}

// ===== Start =====
document.addEventListener('DOMContentLoaded', init);
