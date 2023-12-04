<?php
$resizedImagePath = null;
$error = null;

function canUploadImage($file) {
    $fileExtension = strtolower(pathinfo($file['name'], PATHINFO_EXTENSION));
    $finfo = new finfo(FILEINFO_MIME_TYPE);
    $fileMimeType = $finfo->file($file['tmp_name']);
    $maxFileSize = 500 * 1024;
    return (strpos($fileMimeType, 'image/') === 0 &&
        $fileExtension !== 'php' &&
        $file['size'] <= $maxFileSize &&
        strlen($file['name']) >= 30
    );
}

function resizeImage($file) {
    try {
        $imagick = new \Imagick($file['tmp_name']);
        $imagick->thumbnailImage(50, 50, true, true);
        $filePath = 'results/50x50-' . $file['name'];
        $imagick->writeImage($filePath);
        chmod($filePath, 0444);
        return $filePath;
    } catch (Exception $e) {
        global $error;
        $error = 'Error when doing magic.';
        return null;
    }
}

if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_FILES['image'])) {
    if (canUploadImage($_FILES['image'])) {
        $resizedImagePath = resizeImage($_FILES['image']);
    } else {
        $error = 'Please upload different file.';
    }
}
?>