# Git Initialization Script for Conway's Game of Life v1.1.0
# This script initializes a Git repository and prepares for GitHub upload

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "  Conway's Game of Life v1.1.0" -ForegroundColor Cyan
Write-Host "  Git Repository Initialization" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

# Check if Git is installed
Write-Host "[1/8] Checking for Git installation..." -ForegroundColor Yellow
try {
    $gitVersion = git --version
    Write-Host "✅ Git found: $gitVersion" -ForegroundColor Green
} catch {
    Write-Host "❌ Git is not installed!" -ForegroundColor Red
    Write-Host "Please install Git from: https://git-scm.com/" -ForegroundColor Red
    exit 1
}

Write-Host ""

# Initialize Git repository
Write-Host "[2/8] Initializing Git repository..." -ForegroundColor Yellow
if (Test-Path ".git") {
    Write-Host "⚠️  Git repository already exists" -ForegroundColor Yellow
    $reinit = Read-Host "Do you want to reinitialize? (y/N)"
    if ($reinit -eq "y" -or $reinit -eq "Y") {
        Remove-Item -Recurse -Force .git
        git init
        Write-Host "✅ Repository reinitialized" -ForegroundColor Green
    } else {
        Write-Host "⏭️  Skipping initialization" -ForegroundColor Yellow
    }
} else {
    git init
    Write-Host "✅ Git repository initialized" -ForegroundColor Green
}

Write-Host ""

# Configure Git user (if not set globally)
Write-Host "[3/8] Configuring Git user..." -ForegroundColor Yellow
$userName = git config user.name
$userEmail = git config user.email

if (-not $userName) {
    $userName = Read-Host "Enter your name (for commits)"
    git config user.name "$userName"
    Write-Host "✅ Git user name set: $userName" -ForegroundColor Green
} else {
    Write-Host "✅ Using existing user: $userName" -ForegroundColor Green
}

if (-not $userEmail) {
    $userEmail = Read-Host "Enter your email (for commits)"
    git config user.email "$userEmail"
    Write-Host "✅ Git user email set: $userEmail" -ForegroundColor Green
} else {
    Write-Host "✅ Using existing email: $userEmail" -ForegroundColor Green
}

Write-Host ""

# Check .gitignore
Write-Host "[4/8] Checking .gitignore..." -ForegroundColor Yellow
if (Test-Path ".gitignore") {
    Write-Host "✅ .gitignore found" -ForegroundColor Green
} else {
    Write-Host "⚠️  .gitignore not found" -ForegroundColor Yellow
}

Write-Host ""

# Add all files
Write-Host "[5/8] Adding files to Git..." -ForegroundColor Yellow
git add .
$addedFiles = git status --short
Write-Host "✅ Files staged for commit:" -ForegroundColor Green
git status --short

Write-Host ""

# Initial commit
Write-Host "[6/8] Creating initial commit..." -ForegroundColor Yellow
$commitMessage = "Initial commit - Conway's Game of Life v1.1.0

Features:
- 8 Beautiful color themes
- Time travel (rewind/forward)
- Auto-pause on stable patterns
- Pattern detection system
- Random 3x3 pattern generator
- Real-time statistics
- Interactive drawing and zooming
- Complete OOP architecture with SOLID principles

Documentation:
- Comprehensive README (FR/EN)
- Architecture documentation
- SOLID principles analysis
- Building guide
- Contributing guide

Project satisfies all OOP course requirements."

git commit -m "$commitMessage"
Write-Host "✅ Initial commit created" -ForegroundColor Green

Write-Host ""

# Setup remote (optional)
Write-Host "[7/8] Setting up GitHub remote..." -ForegroundColor Yellow
Write-Host "Do you want to add a GitHub remote repository?" -ForegroundColor Cyan
Write-Host "(You should create an empty repository on GitHub first)" -ForegroundColor Gray
$addRemote = Read-Host "Add remote? (y/N)"

if ($addRemote -eq "y" -or $addRemote -eq "Y") {
    Write-Host ""
    Write-Host "GitHub Repository URL examples:" -ForegroundColor Gray
    Write-Host "  https://github.com/username/GameOfLife.git" -ForegroundColor Gray
    Write-Host "  git@github.com:username/GameOfLife.git" -ForegroundColor Gray
    Write-Host ""
    
    $remoteUrl = Read-Host "Enter your GitHub repository URL"
    
    if ($remoteUrl) {
        try {
            git remote add origin $remoteUrl
            Write-Host "✅ Remote 'origin' added: $remoteUrl" -ForegroundColor Green
            
            Write-Host ""
            Write-Host "Do you want to push to GitHub now?" -ForegroundColor Cyan
            $pushNow = Read-Host "Push now? (y/N)"
            
            if ($pushNow -eq "y" -or $pushNow -eq "Y") {
                Write-Host "Pushing to GitHub..." -ForegroundColor Yellow
                git branch -M main
                git push -u origin main
                Write-Host "✅ Pushed to GitHub successfully!" -ForegroundColor Green
            } else {
                Write-Host "⏭️  Skipping push. You can push later with: git push -u origin main" -ForegroundColor Yellow
            }
        } catch {
            Write-Host "❌ Error adding remote: $_" -ForegroundColor Red
        }
    }
} else {
    Write-Host "⏭️  Skipping remote setup" -ForegroundColor Yellow
    Write-Host "You can add it later with: git remote add origin <URL>" -ForegroundColor Gray
}

Write-Host ""

# Summary
Write-Host "[8/8] Summary" -ForegroundColor Yellow
Write-Host "========================================" -ForegroundColor Cyan
Write-Host "✅ Git repository initialized" -ForegroundColor Green
Write-Host "✅ User configured: $userName <$userEmail>" -ForegroundColor Green
Write-Host "✅ Initial commit created" -ForegroundColor Green

$remoteUrl = git remote get-url origin 2>$null
if ($remoteUrl) {
    Write-Host "✅ Remote configured: $remoteUrl" -ForegroundColor Green
}

Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

# Next steps
Write-Host "📋 Next Steps:" -ForegroundColor Cyan
Write-Host ""
Write-Host "1. Take screenshots:" -ForegroundColor White
Write-Host "   .\take_screenshots.ps1" -ForegroundColor Gray
Write-Host ""
Write-Host "2. Build the installer (if Inno Setup installed):" -ForegroundColor White
Write-Host '   & "C:\Program Files (x86)\Inno Setup 6\ISCC.exe" installer\GameOfLife_Installer.iss' -ForegroundColor Gray
Write-Host ""
Write-Host "3. If you added screenshots or made changes:" -ForegroundColor White
Write-Host "   git add ." -ForegroundColor Gray
Write-Host '   git commit -m "Add screenshots and installer"' -ForegroundColor Gray
Write-Host "   git push" -ForegroundColor Gray
Write-Host ""
Write-Host "4. Create a GitHub release:" -ForegroundColor White
Write-Host "   - Go to your GitHub repository" -ForegroundColor Gray
Write-Host "   - Click 'Releases' → 'Create a new release'" -ForegroundColor Gray
Write-Host "   - Tag: v1.1.0" -ForegroundColor Gray
Write-Host "   - Upload GameOfLife_Setup_v1.1.0.exe" -ForegroundColor Gray
Write-Host ""

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "🎉 Repository ready for GitHub!" -ForegroundColor Green
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

# Show current status
Write-Host "Current Git Status:" -ForegroundColor Cyan
git status
Write-Host ""

Write-Host "Git Log:" -ForegroundColor Cyan
git log --oneline -n 5
Write-Host ""

Write-Host "Press any key to exit..." -ForegroundColor Gray
$null = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")
