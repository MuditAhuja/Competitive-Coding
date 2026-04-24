import { useState } from 'react';

function App() {
  const [dataset, setDataset] = useState('1');
  const [algorithm, setAlgorithm] = useState('1');
  const [loading, setLoading] = useState(false);
  const [result, setResult] = useState(null);
  const [viewMode, setViewMode] = useState('sorted'); // 'original' or 'sorted'

  const handleSort = async () => {
    setLoading(true);
    setResult(null);
    try {
      const response = await fetch('http://localhost:3001/api/sort', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ dataset, algorithm })
      });
      const data = await response.json();
      if (data.error) {
        alert(data.error);
      } else {
        setResult(data);
        setViewMode('sorted');
      }
    } catch (err) {
      console.error(err);
      alert("Failed to connect to backend");
    } finally {
      setLoading(false);
    }
  };

  const currentData = viewMode === 'original' ? result?.originalData : result?.sortedData;

  // For data bars scaling
  const maxVal = currentData ? Math.max(...currentData.map(d => typeof d.value === 'number' && !isNaN(d.value) ? d.value : 0), 1) : 100;

  return (
    <div className="app-container">
      <header className="header">
        <h1>Smart Sorting Studio</h1>
        <p>A Web Interface for high-performance C++ sorting algorithms</p>
      </header>

      <section className="glass-panel controls">
        <div className="control-group">
          <label>Dataset</label>
          <select value={dataset} onChange={e => setDataset(e.target.value)} disabled={loading}>
            <option value="1">Marks Dataset (Numeric Focus)</option>
            <option value="2">Sales Dataset (Large Range)</option>
            <option value="3">Logs Dataset (Detailed)</option>
          </select>
        </div>

        <div className="control-group">
          <label>Algorithm</label>
          <select value={algorithm} onChange={e => setAlgorithm(e.target.value)} disabled={loading}>
            <option value="1">Merge Sort (O(n log n), Stable)</option>
            <option value="2">Quick Sort (O(n log n), Unstable)</option>
            <option value="3">Heap Sort (O(n log n))</option>
            <option value="4">Counting Sort (O(n+k))</option>
            <option value="5">Radix Sort (O(nk))</option>
            <option value="6">Bucket Sort</option>
          </select>
        </div>

        <button onClick={handleSort} disabled={loading}>
          {loading ? (
            <>
              <div className="loader"></div>
              Processing...
            </>
          ) : (
            'Run Algorithm'
          )}
        </button>
      </section>

      <section className="results-area">
        <div className="glass-panel data-visualization">
          {result ? (
            <>
              <div className="visualization-controls">
                <button 
                  className={`view-toggle ${viewMode === 'original' ? 'active' : ''}`}
                  onClick={() => setViewMode('original')}
                  style={{margin: 0, padding: '8px 16px', background: viewMode==='original' ? 'var(--accent)' : 'rgba(15, 23, 42, 0.5)'}}
                >
                  Original
                </button>
                <button 
                  className={`view-toggle ${viewMode === 'sorted' ? 'active' : ''}`}
                  onClick={() => setViewMode('sorted')}
                  style={{margin: 0, padding: '8px 16px', background: viewMode==='sorted' ? 'var(--accent)' : 'rgba(15, 23, 42, 0.5)'}}
                >
                  Sorted
                </button>
              </div>
              <div className="data-bars">
                {currentData && currentData.map((item, idx) => {
                  const val = typeof item.value === 'number' && !isNaN(item.value) ? item.value : 0;
                  const heightPercent = val === 0 ? 5 : Math.max(((val / maxVal) * 100), 5);
                  
                  return (
                    <div className="bar-container" key={`${item.name}-${idx}`}>
                      <div 
                        className="bar" 
                        style={{ height: `${heightPercent}%` }}
                      >
                         <span className="bar-value">{item.value}</span>
                      </div>
                      <span className="bar-label" title={item.name}>{item.name.substring(0,6)}</span>
                    </div>
                  );
                })}
              </div>
            </>
          ) : (
            <div className="empty-state">
              Select dataset and algorithm to begin
            </div>
          )}
        </div>

        {result && result.performance && (
          <div className="metrics-grid">
            <div className="metric-card">
              <h4>Time Taken</h4>
              <p>{result.performance.timeTaken || '0 ms'}</p>
            </div>
            <div className="metric-card">
              <h4>Comparisons</h4>
              <p>{result.performance.comparisons || '0'}</p>
            </div>
            <div className="metric-card">
              <h4>Swaps</h4>
              <p>{result.performance.swaps || '0'}</p>
            </div>
            <div className="metric-card">
              <h4>Stable</h4>
              <p>{result.performance.stable || 'N/A'}</p>
            </div>
            <div className="metric-card metric-desc">
              <h4>Algorithm Description</h4>
              <p>{result.performance.description || result.performance.algorithm || ''}</p>
            </div>
          </div>
        )}
      </section>
    </div>
  );
}

export default App;
