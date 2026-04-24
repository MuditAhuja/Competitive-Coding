const express = require('express');
const cors = require('cors');
const { spawn } = require('child_process');
const path = require('path');

const app = express();
app.use(cors());
app.use(express.json());

app.post('/api/sort', (req, res) => {
    const { dataset, algorithm } = req.body;
    
    if (!dataset || !algorithm) {
        return res.status(400).json({ error: 'Missing dataset or algorithm' });
    }

    const exePath = path.join(__dirname, '..', '..', 'sortingstudio.exe');
    const child = spawn(exePath, [], { cwd: path.join(__dirname, '..', '..') });

    let output = '';
    let errorOutput = '';

    child.stdout.on('data', (data) => {
        output += data.toString();
    });

    child.stderr.on('data', (data) => {
        errorOutput += data.toString();
    });

    child.on('close', (code) => {
        if (code !== 0) {
            console.error('C++ Process Error:', errorOutput);
            return res.status(500).json({ error: 'Failed to run sorting process' });
        }

        try {
            const extractList = (startStr, endStr) => {
                const startIndex = output.indexOf(startStr);
                if (startIndex === -1) return [];
                const actualStart = startIndex + startStr.length;
                let endIndex = endStr ? output.indexOf(endStr, actualStart) : output.length;
                if (endIndex === -1) endIndex = output.length;
                
                const lines = output.substring(actualStart, endIndex)
                  .split('\n')
                  .map(line => line.trim())
                  .filter(line => line.includes('-') && !line.includes('====') && !line.includes('Time Taken'));

                return lines.map(line => {
                    const [name, val] = line.split('-').map(p => p.trim());
                    return { name, value: parseInt(val, 10) || val };
                });
            };

            const originalData = extractList('Original Dataset:', 'Choose Sorting Algorithm:');
            const sortedData = extractList('Sorted Dataset:', '===== PERFORMANCE REPORT =====');

            const extractMetric = (metricName) => {
                const lines = output.split('\n');
                const line = lines.find(l => l.startsWith(metricName));
                if (line) {
                    return line.split(':')[1]?.trim() || '';
                }
                return '';
            };

            const performance = {
                algorithm: extractMetric('Algorithm'),
                timeTaken: extractMetric('Time Taken'),
                comparisons: extractMetric('Comparisons'),
                swaps: extractMetric('Swaps'),
                stable: extractMetric('Stable'),
                description: extractMetric('Description')
            };

            res.json({ originalData, sortedData, performance, rawOutput: output });
        } catch (e) {
            console.error(e);
            res.status(500).json({ error: 'Error parsing C++ output' });
        }
    });

    // Send inputs
    child.stdin.write(`${dataset}\n`);
    child.stdin.write(`${algorithm}\n`);
    child.stdin.end();
});

const PORT = 3001;
app.listen(PORT, () => {
    console.log(`Backend wrapper running on http://localhost:${PORT}`);
});
