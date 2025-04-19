import * as THREE from 'three';

// Scene setup
const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
const renderer = new THREE.WebGLRenderer({ antialias: true });
renderer.setSize(window.innerWidth, window.innerHeight);
document.body.appendChild(renderer.domElement);

// Lighting
const ambientLight = new THREE.AmbientLight(0x404040);
scene.add(ambientLight);
const directionalLight = new THREE.DirectionalLight(0xffffff, 0.5);
directionalLight.position.set(1, 1, 1);
scene.add(directionalLight);

// Camera position
camera.position.z = 5;

// 4D Grid system
class Grid4D {
    constructor(size, resolution) {
        this.size = size;
        this.resolution = resolution;
        this.points = [];
        this.generateGrid();
    }

    generateGrid() {
        for (let x = -this.size; x <= this.size; x += this.resolution) {
            for (let y = -this.size; y <= this.size; y += this.resolution) {
                for (let z = -this.size; z <= this.size; z += this.resolution) {
                    for (let w = -this.size; w <= this.size; w += this.resolution) {
                        // Create a point in 4D space
                        const point = new THREE.Vector4(x, y, z, w);
                        this.points.push(point);
                    }
                }
            }
        }
    }

    // Project 4D point to 3D space
    projectTo3D(point4D, wOffset = 0) {
        const w = point4D.w + wOffset;
        const scale = 1 / (w + 2); // Perspective projection
        return new THREE.Vector3(
            point4D.x * scale,
            point4D.y * scale,
            point4D.z * scale
        );
    }
}

// Create grid
const grid = new Grid4D(2, 0.5);

// Create points in 3D space
const points = new THREE.Points(
    new THREE.BufferGeometry(),
    new THREE.PointsMaterial({ color: 0xffffff, size: 0.05 })
);
scene.add(points);

// Animation variables
let wOffset = 0;
const wSpeed = 0.01;

// Animation loop
function animate() {
    requestAnimationFrame(animate);

    // Update w-offset for 4D rotation
    wOffset += wSpeed;

    // Update points positions
    const positions = [];
    grid.points.forEach(point4D => {
        const point3D = grid.projectTo3D(point4D, wOffset);
        positions.push(point3D.x, point3D.y, point3D.z);
    });

    points.geometry.setAttribute(
        'position',
        new THREE.Float32BufferAttribute(positions, 3)
    );

    renderer.render(scene, camera);
}

// Handle window resize
window.addEventListener('resize', () => {
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
    renderer.setSize(window.innerWidth, window.innerHeight);
});

// Start animation
animate(); 