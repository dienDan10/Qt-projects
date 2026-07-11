// generate-csv.js

const fs = require('fs');

const n = parseInt(process.argv[2], 10);

if (isNaN(n) || n <= 0) {
    console.error('Usage: node generate-csv.js <number_of_rows>');
    process.exit(1);
}

const headers = [
    'ID',
    'Name',
    'Department',
    'Age',
    'Salary',
    'City',
    'JoinDate',
    'Status',
];

const departments = [
    'Engineering',
    'Marketing',
    'Finance',
    'HR',
    'Sales',
    'Operations',
];

const cities = ['Hanoi', 'HCMC', 'Da Nang', 'Can Tho', 'Hai Phong'];

const statuses = ['Active', 'Inactive', 'On Leave'];

const firstNames = [
    'An',
    'Binh',
    'Cuong',
    'Dung',
    'Ha',
    'Linh',
    'Minh',
    'Nam',
    'Phuong',
    'Trang',
];

const lastNames = ['Nguyen', 'Tran', 'Le', 'Pham', 'Hoang', 'Vu', 'Dang'];

function randomItem(arr) {
    return arr[Math.floor(Math.random() * arr.length)];
}

function randomDate() {
    const start = new Date(2018, 0, 1);
    const end = new Date();

    const date = new Date(
        start.getTime() + Math.random() * (end.getTime() - start.getTime()),
    );

    return date.toISOString().slice(0, 10);
}

function randomName() {
    return `${randomItem(lastNames)} Van ${randomItem(firstNames)}`;
}

const lines = [headers.join(',')];

for (let i = 1; i <= n; i++) {
    const row = [
        i,
        randomName(),
        randomItem(departments),
        Math.floor(Math.random() * 25) + 22,
        Math.floor(Math.random() * 2500) + 1000,
        randomItem(cities),
        randomDate(),
        randomItem(statuses),
    ];

    lines.push(row.join(','));
}

fs.writeFileSync('employees.csv', lines.join('\n'));

console.log(`Generated ${n} rows in employees.csv`);
